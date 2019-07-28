#include <utility>

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <chrono>
#include <filesystem>
#include <libplatform/libplatform.h>
#include <v8.h>
#include <functional>
#include <sw/object_wrap.hpp>
#include <sw/math/vector.hpp>
#include <sw/math/matrix.hpp>
#include <sw/sw_macros.hpp>
#include <sw/sprite.hpp>
#include <glslcross.h>

extern "C" const char js_bundle_contents[];

using namespace v8;

double r() {
    return (double) rand() / RAND_MAX * 1000;
}

void Start() {
    // Test crosscompilation
    glslcross::ShaderProgram program;
    program.GetShaderData(glslcross::ShaderProgram::Stage::Vertex).source =
            "#version 450\nvoid main() { gl_Position = vec4(0); }";
    program.GetShaderData(glslcross::ShaderProgram::Stage::Fragment).source =
            "#version 330 core\nvoid main() { gl_FragColor = vec4(0); }";
    if (!program.Crosscompile(110, true)) {
        std::cout << program.GetInfoLog() << std::endl;
    } else {
        std::cout << program.GetShaderData(glslcross::ShaderProgram::Stage::Vertex).GetCrosscompiledSource() << std::endl;
        std::cout << program.GetShaderData(glslcross::ShaderProgram::Stage::Fragment).GetCrosscompiledSource() << std::endl;
    }


    const double d1[] = {r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r()};
    const double d2[] = {r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r()};
    const double d3[] = {r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r()};
    sw::Matrix4 m1(d1);
    sw::Matrix4 m2(d2);
    sw::Matrix4 m3(d3);
    sw::Vector4 v(r(), r(), r(), r());

    auto result1 = m1 * m2 * m3 * v;
    auto result2 = m1 * (m2 * (m3 * v));

    std::cout << std::setprecision(100);
    std::cout << result1.x << " " << result1.y << " " << result1.z << " " << result1.w << std::endl;
    std::cout << result2.x << " " << result2.y << " " << result2.z << " " << result2.w << std::endl;


    // Initialize V8.
    //V8::InitializeICUDefaultLocation(argv[0]);
    //V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();
    V8::InitializePlatform(platform.get());
    V8::Initialize();

    // Create a new Isolate and make it the current one.
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
    Isolate *isolate = Isolate::New(create_params);

    {
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);

        Local<Context> context = Context::New(isolate);
        Context::Scope context_scope(context);

        Local<Object> sw_object(Object::New(Isolate::GetCurrent()));
        context->Global()->Set(Isolate::GetCurrent()->GetCurrentContext(),
                               String::NewFromUtf8(isolate, "sw").ToLocalChecked(), sw_object);

        sw_object->Set(Isolate::GetCurrent()->GetCurrentContext(),
                       String::NewFromUtf8(isolate, "Vector2").ToLocalChecked(),
                       sw::ObjectWrap::GetObjectConstructorTemplate<sw::Vector2>()->GetFunction(
                               context).ToLocalChecked());

        sw_object->Set(Isolate::GetCurrent()->GetCurrentContext(),
                       String::NewFromUtf8(isolate, "Vector3").ToLocalChecked(),
                       sw::ObjectWrap::GetObjectConstructorTemplate<sw::Vector3>()->GetFunction(
                               context).ToLocalChecked());

        sw_object->Set(Isolate::GetCurrent()->GetCurrentContext(),
                       String::NewFromUtf8(isolate, "Sprite").ToLocalChecked(),
                       sw::ObjectWrap::GetObjectConstructorTemplate<sw::Sprite>()->GetFunction(
                               context).ToLocalChecked());


        context->Global()->Get(Isolate::GetCurrent()->GetCurrentContext(), v8_str("console")).ToLocalChecked()->
                ToObject(context).ToLocalChecked()->
                Set(Isolate::GetCurrent()->GetCurrentContext(),
                    String::NewFromUtf8(isolate, "log").ToLocalChecked(),
                    FunctionTemplate::New(isolate, [](auto info) {
                        std::string s;
                        for (int i = 0; i < info.Length(); ++i) {
                            s += *v8::String::Utf8Value(Isolate::GetCurrent(),
                                    info[i]->ToString(Isolate::GetCurrent()->GetCurrentContext()).ToLocalChecked());
                            s += " ";
                        }
                        std::cout << s << std::endl;
                    })->GetFunction(context).ToLocalChecked()
        );

        Local<String> source = String::NewFromUtf8(Isolate::GetCurrent(), js_bundle_contents).ToLocalChecked();
        Local<Script> script = Script::Compile(Isolate::GetCurrent()->GetCurrentContext(), source).ToLocalChecked();

        TryCatch t(Isolate::GetCurrent());

        script->Run(Isolate::GetCurrent()->GetCurrentContext());

        if (t.HasCaught()) {
            std::cerr << *String::Utf8Value(Isolate::GetCurrent(), t.Exception()) << std::endl;
        }

        double delta;
        auto current = std::chrono::high_resolution_clock::now();
        while (true) {
            delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - current).count() / 1000000000.0;
            current = std::chrono::high_resolution_clock::now();
            auto f = sw_object->Get(context, v8_str("update")).ToLocalChecked();
            if (f.IsEmpty() || !f->IsFunction()) break;
            auto d = v8_num(delta).As<Value>();
            f.As<Function>()->Call(context, sw_object, 1, &d);
            if (t.HasCaught()) {
                std::cerr << *String::Utf8Value(Isolate::GetCurrent(), t.Exception()) << std::endl;
                break;
            }
        }


    }



    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
}