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
#include "scene_node.hpp"

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

    int static_var = 12345;

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
            int Get() {
                std::cout << "GOT" << std::endl;
                return o;
            }
            void Set(int a) {
                std::cout << "SET" << std::endl;
                v->resize(2);
                o = a;
            }
            double GetIndexed(int i) {
                std::cout << "GET INDEXED " << i << std::endl;
                return i * 15.0;
            }
            void SetIndexed(int i, double d) {
                std::cout << "SET INDEXED " << i << " " << d << std::endl;
            }
            std::shared_ptr<std::vector<int>> v = std::make_shared<std::vector<int>>();
        };

        v8b::Class<sw::Vector2> c(isolate);
        c
            .Constructor<std::tuple<>, std::tuple<double>, std::tuple<double, double>, std::tuple<const sw::Vector2 &>>()
            .Var("x", &sw::Vector2::x)
            .Var("y", &sw::Vector2::y)
            .Function("length", &sw::Vector2::Length)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("dot", &sw::Vector2::Dot, &sw::Vector2::Dot)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("distance", &sw::Vector2::Distance, &sw::Vector2::Distance)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("determinant", &sw::Vector2::Determinant, &sw::Vector2::Determinant)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("angle", &sw::Vector2::Angle, &sw::Vector2::Angle)
            .Function("normalized", &sw::Vector2::Normalized)
            .Function("lengthSquared", &sw::Vector2::LengthSquared)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("distanceSquared", &sw::Vector2::DistanceSquared, &sw::Vector2::DistanceSquared)
            .Function("perpendicular", &sw::Vector2::Perpendicular)
            .Function<
                sw::Vector2 (sw::Vector2::*)(double, double) const,
                sw::Vector2 (sw::Vector2::*)(const sw::Vector2 &) const>
                ("min", &sw::Vector2::Min, &sw::Vector2::Min)
            .Function<
                sw::Vector2 (sw::Vector2::*)(double, double) const,
                sw::Vector2 (sw::Vector2::*)(const sw::Vector2 &) const>
                ("max", &sw::Vector2::Max, &sw::Vector2::Max)
            .Function("toString", [](sw::Vector2 &v) -> std::string {
                return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
            })
            .StaticFunction("staticFunction", []() {
                std::cout << "static function call" << std::endl;
            })
            .StaticVar("staticVar", &static_var)
            .AutoWrap()
            .PointerAutoWrap()
        ;

        v8b::Class<Z> z(isolate);
        z
            .Constructor<std::tuple<>>()
            .Var("o", &Z::o)
            .Var("v", &Z::v)
            .Property("op", &Z::Get, &Z::Set)
            .Indexer(&Z::GetIndexed, &Z::SetIndexed)
            .AutoWrap()
            .PointerAutoWrap()
            .Inherit<sw::Vector2>()
        ;

        v8b::Class<std::vector<int>> vec(isolate);
        vec
            .Property("length", [](std::vector<int> &v) {
                return v.size();
            })
            .Indexer([](std::vector<int> &v, int index) {
                return v[index];
            }, [](std::vector<int> &v, int index, int i) {
                v[index] = i;
            })
            .Function("toString", [](std::vector<int> &v) {
                std::string s;
                for (int i : v) {
                    s += std::to_string(i) + ", ";
                }
                return "[" + (s.empty() ? s : s.substr(0, s.size() - 2)) + "]";
            })
            .AutoWrap()
            .PointerAutoWrap()
        ;

        sw::SceneNode::Create();

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