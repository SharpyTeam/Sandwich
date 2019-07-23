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
#include <sw/sw_macros.hpp>
#include <sw/sprite.hpp>

extern "C" const char js_bundle_contents[];

using namespace v8;

void Start() {
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
                       sw::ObjectWrap::GetObjectConstructorTemplate<sw::Vector<2>>()->GetFunction(context).ToLocalChecked());

        sw_object->Set(Isolate::GetCurrent()->GetCurrentContext(),
                String::NewFromUtf8(isolate, "Vector3").ToLocalChecked(),
                       sw::ObjectWrap::GetObjectConstructorTemplate<sw::Vector<3>>()->GetFunction(context).ToLocalChecked());

        sw_object->Set(Isolate::GetCurrent()->GetCurrentContext(),
                       String::NewFromUtf8(isolate, "Sprite").ToLocalChecked(),
                       sw::ObjectWrap::GetObjectConstructorTemplate<sw::Sprite>()->GetFunction(context).ToLocalChecked());


        context->Global()->Get(Isolate::GetCurrent()->GetCurrentContext(), v8_str("console")).ToLocalChecked()->
        ToObject(context).ToLocalChecked()->
                Set(Isolate::GetCurrent()->GetCurrentContext(),
                        String::NewFromUtf8(isolate, "log").ToLocalChecked(),
                    FunctionTemplate::New(isolate, [](auto info) {
                        String::Utf8Value utf8(info.GetIsolate(), info[0]);
                        std::cout << *utf8 << std::endl;
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