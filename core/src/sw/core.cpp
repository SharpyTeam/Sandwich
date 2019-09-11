#include <sw/modules/math.hpp>

#include <v8bind/v8bind.hpp>

#include <libplatform/libplatform.h>
#include <v8.h>

#include <iostream>
#include <chrono>
#include <sw/test/std_calculator.hpp>

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
        // Initialize scopes
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);

        v8b::Module global(isolate);
        v8b::Module sw(isolate);
        v8b::Module console(isolate);

        console.Function("log", [](const FunctionCallbackInfo<Value> &info) {
            std::string s;
            for (int i = 0; i < info.Length(); ++i) {
                s += *v8::String::Utf8Value(Isolate::GetCurrent(),
                                            info[i]->ToString(Isolate::GetCurrent()->GetCurrentContext()).ToLocalChecked());
                s += " ";
            }
            std::cout << s << std::endl;
        });

        global.Submodule("sw", sw);

        sw.Class("Vector2", v8b::Class<sw::Vector2>(isolate));

        Local<Context> context = Context::New(isolate, nullptr, global.GetObjectTemplate());
        Context::Scope context_scope(context);

        // Override default dummy console
        context->Global()->Set(context, v8b::ToV8(isolate, "console"), console.NewInstance());

        // Compile script
        Local<Script> script = Script::Compile(Isolate::GetCurrent()->GetCurrentContext(),
                                               v8b::ToV8(isolate, js_bundle_contents)).ToLocalChecked();

        // Set try-catch and run script
        TryCatch t(Isolate::GetCurrent());
        script->Run(Isolate::GetCurrent()->GetCurrentContext());

        double delta;
        auto current = std::chrono::high_resolution_clock::now();
        while (true) {
            // Check errors
            if (t.HasCaught()) {
                std::cerr << *String::Utf8Value(Isolate::GetCurrent(), t.Exception()) << std::endl;
                break;
            }

            delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - current).count() / 1000000000.0;
            current = std::chrono::high_resolution_clock::now();

            // Get update function and call it
            auto sw_object = context->Global()->Get(context, v8b::ToV8(isolate, "sw")).ToLocalChecked().As<v8::Object>();
            auto f = sw_object->Get(context, v8b::ToV8(isolate, "update")).ToLocalChecked();
            if (f.IsEmpty() || !f->IsFunction()) break;
            auto d = v8b::ToV8(isolate, delta).As<Value>();
            f.As<Function>()->Call(context, sw_object, 1, &d);
        }

        v8b::ClassManagerPool::RemoveAll(isolate);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
}