#include <utility>

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <chrono>
#include <libplatform/libplatform.h>
#include <v8.h>
#include <functional>
#include <sw/math/vector.hpp>
#include <sw/math/matrix.hpp>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <sw/sw_macros.hpp>
#include <sw/modules/math.hpp>
#include <v8bind/function.hpp>
#include <v8bind/type_info.hpp>
#include <v8bind/class.hpp>
#include <v8bind/class.ipp>

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

    {
        // Initialize scopes
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);

        // Set context
        Local<Context> context = Context::New(isolate);
        Context::Scope context_scope(context);

        struct Z : public sw::Vector2 {
            int o = 10;
        };

        v8b::Class<sw::Vector2> c(isolate);
        c
            .Constructor<std::tuple<double>, std::tuple<double, double>>()
            .Var("x", &sw::Vector2::x)
            .Var("y", &sw::Vector2::y)
            .AutoWrap()
            .PointerAutoWrap()
        ;

        v8b::Class<Z> z(isolate);
        z
            .Constructor<std::tuple<>>()
            .Var("o", &Z::o)
            .AutoWrap()
            .PointerAutoWrap()
            .Inherit<sw::Vector2>()
        ;

        context->Global()->Set(context, v8_str("Z"), z.GetFunctionTemplate()->GetFunction(context).ToLocalChecked());
        context->Global()->Set(context, v8_str("Vector2"), c.GetFunctionTemplate()->GetFunction(context).ToLocalChecked());

        // Set global properties
        context->Global()->Set(context, v8_str("console"), GetConsole());
        context->Global()->Set(context, v8_str("sw"), GetSwObject());
        //context->Global()->Set(context, v8_str("test"), v8b::wrap_function(isolate, static_cast<void(*)(int, int)>(f), static_cast<void(*)(int)>(f), static_cast<void(*)(std::string &&)>(f))->GetFunction(context).ToLocalChecked());

        //sw::MathModule math_module();

        //const sw::JSModule js_modules[] = {math_module};

        //for (const sw::JSModule &js_module : js_modules)
            //js_module.Init(isolate);

        /*v8pp::class_<A> a(isolate);
        a.auto_wrap_objects().indexer(&A::Get, &A::Set).var("x", &A::x).function("toString", &A::ToString).
        ctor<int>();

        A *aa = new A(12);
        aa->children.push_back(new A(1));
        aa->children.push_back(new A(32));*/

        //GetSwObject()->Set(context, v8_str("a"), v8pp::to_v8(isolate, *aa));

        // Compile script
        Local<Script> script = Script::Compile(Isolate::GetCurrent()->GetCurrentContext(),
                                               v8_str(js_bundle_contents)).ToLocalChecked();

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
            auto f = GetSwObject()->Get(context, v8_str("update")).ToLocalChecked();
            if (f.IsEmpty() || !f->IsFunction()) break;
            auto d = v8_num(delta).As<Value>();
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