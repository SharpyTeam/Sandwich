#include <utility>

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <filesystem>
#include <libplatform/libplatform.h>
#include <v8.h>
#include <functional>
#include <object_wrap.hpp>
#include <math/vector.hpp>
#include <sw_macros.hpp>

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
        context->Global()->Set(String::NewFromUtf8(isolate, "sw").ToLocalChecked(), sw_object);

        auto v = new sw::Vector3;
        v->x = 131;
        v->y = 132;
        v->z = 133;
        v->Wrap();

        sw_object->Set(String::NewFromUtf8(isolate, "Vector3").ToLocalChecked(),
                       v->GetObjectConstructorTemplate()->GetFunction(context).ToLocalChecked());

        sw_object->Set(v8_str("vvv"), v->GetHandle());


        context->Global()->Get(String::NewFromUtf8(isolate, "console").ToLocalChecked())->ToObject(
                context).ToLocalChecked()->
                Set(String::NewFromUtf8(isolate, "log").ToLocalChecked(),
                    FunctionTemplate::New(isolate, [](auto info) {
                        String::Utf8Value utf8(info.GetIsolate(), info[0]);
                        std::cout << *utf8 << std::endl;
                    })->GetFunction(context).ToLocalChecked()
        );

        Local<String> source = String::NewFromUtf8(Isolate::GetCurrent(), js_bundle_contents).ToLocalChecked();
        Local<Script> script = Script::Compile(Isolate::GetCurrent()->GetCurrentContext(), source).ToLocalChecked();

        TryCatch t(Isolate::GetCurrent());

        script->Run(Isolate::GetCurrent()->GetCurrentContext());

        std::cout << "C++: " << v->x << std::endl;
        std::cout << "C++: " << v->y << std::endl;
        std::cout << "C++: " << v->z << std::endl;

        if (t.HasCaught()) {
            std::cerr << *String::Utf8Value(Isolate::GetCurrent(), t.Exception()) << std::endl;
        }
    }



    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
}