#include <sw/modules/math.hpp>

#include <v8bind/v8bind.hpp>

#include <libplatform/libplatform.h>
#include <v8.h>
#include <v8pp/module.hpp>

#include <iostream>
#include <chrono>
#include <sw/test/std_calculator.hpp>

extern "C" const char js_bundle_contents[];

using namespace v8;

Local<Object> GetSwObject() {
    static Local<Object> sw_object;

    if (!sw_object.IsEmpty())
        return sw_object;

    v8pp::module sw_def(Isolate::GetCurrent());
    sw_object = sw_def.new_instance();

    return sw_object;
}

Local<Object> GetConsole() {
    static Local<Object> console_object;

    if (!console_object.IsEmpty())
        return console_object;

    v8pp::module console_def(Isolate::GetCurrent());

    console_def.function("log", [](const FunctionCallbackInfo<Value> &info) {
        std::string s;
        for (int i = 0; i < info.Length(); ++i) {
            s += *v8::String::Utf8Value(Isolate::GetCurrent(),
                                        info[i]->ToString(Isolate::GetCurrent()->GetCurrentContext()).ToLocalChecked());
            s += " ";
        }
        std::cout << s << std::endl;
    });

    console_object = console_def.new_instance();

    return console_object;
}

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

    std::cout << ">>> Calculator test" << std::endl;

    sw::StdCalculator calc({"1", "2", "+", "4", "*", "3", "+"});
    std::cout << "Expression '1, 2, +, 4, *, 3, +' evaluated, result: " << calc.GetResult() << std::endl;

    std::cout << ">>> Calculator test finished" << std::endl;

    {
        // Initialize scopes
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);

        // Set context
        Local<Context> context = Context::New(isolate);
        Context::Scope context_scope(context);

        v8b::Class<sw::Vector2> v(isolate);

        // Set global properties
        context->Global()->Set(context, v8b::ToV8(isolate, "console"), GetConsole());
        context->Global()->Set(context, v8b::ToV8(isolate, "sw"), GetSwObject());

        GetSwObject()->Set(context, v8b::ToV8(isolate, "Vector2"), v.GetFunctionTemplate()->GetFunction(context).ToLocalChecked());

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
            auto f = GetSwObject()->Get(context, v8b::ToV8(isolate, "update")).ToLocalChecked();
            if (f.IsEmpty() || !f->IsFunction()) break;
            auto d = v8b::ToV8(isolate, delta).As<Value>();
            f.As<Function>()->Call(context, GetSwObject(), 1, &d);
        }

        v8b::ClassManagerPool::RemoveAll(isolate);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
}