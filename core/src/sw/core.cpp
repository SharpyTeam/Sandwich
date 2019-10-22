#include <sw/modules/math.hpp>

#include <v8bind/v8bind.hpp>

#include <libplatform/libplatform.h>
#include <v8.h>

#include <iostream>
#include <chrono>

#include <sw/renderer/gl.hpp>
#include <sw/renderer/sprite_batch.hpp>

#include <sw/renderer/renderer.hpp>

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
        v8b::Module math(isolate);
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
        sw.Submodule("math", math);

        math.Class("Vector2", v8b::Class<sw::math::Vector2>(isolate));
        math.Class("Matrix4", v8b::Class<sw::math::Matrix4>(isolate));

        {
            v8b::Class<sw::TextureData> m(isolate);
            m.Constructor<std::tuple<int, int>>();
            m.Function<void(sw::TextureData::*)(int, int, float, float, float, float)>("setPixel", &sw::TextureData::SetPixel);
            m.AutoWrap().PointerAutoWrap();
        }

        {
            v8b::Class<sw::Texture> m(isolate);
            m.StaticFunction<std::shared_ptr<sw::Texture>(*)(const sw::TextureData &)>("create", &sw::Texture::Create);
            m.AutoWrap().PointerAutoWrap();
        }

        {
            v8b::Class<sw::SpriteBatch> m(isolate);
            m.Constructor<std::tuple<>>();
            m.Function("setProjectionMatrix", &sw::SpriteBatch::SetProjectionMatrix);
            m.Function<void(sw::SpriteBatch::*)(const std::shared_ptr<sw::Texture> &, double, double, double, double, double, double, double, bool, bool)>("draw", &sw::SpriteBatch::Draw);
            m.Function("begin", &sw::SpriteBatch::Begin);
            m.Function("end", &sw::SpriteBatch::End);
            m.AutoWrap().PointerAutoWrap();
        }

        sw.Class("TextureData", v8b::Class<sw::TextureData>(isolate));
        sw.Class("Texture", v8b::Class<sw::Texture>(isolate));
        sw.Class("SpriteBatch", v8b::Class<sw::SpriteBatch>(isolate));

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

        sw::Renderer::Init();

        auto sw_object = context->Global()->Get(context, v8b::ToV8(isolate, "sw")).ToLocalChecked().As<v8::Object>();
        auto f = sw_object->Get(context, v8b::ToV8(isolate, "init")).ToLocalChecked();
        if (!f.IsEmpty() && f->IsFunction()) {
            f.As<Function>()->Call(context, sw_object, 0, nullptr);
        }


        double delta;
        auto current = std::chrono::high_resolution_clock::now();

        sw::Renderer::Loop([&]() {
            // Check errors
            if (t.HasCaught()) {
                std::cerr << *String::Utf8Value(Isolate::GetCurrent(), t.Exception()) << std::endl;
                return false;
            }

            delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - current).count() / 1000000000.0;
            current = std::chrono::high_resolution_clock::now();

            // Get update function and call it
            auto sw_object = context->Global()->Get(context, v8b::ToV8(isolate, "sw")).ToLocalChecked().As<v8::Object>();
            auto f = sw_object->Get(context, v8b::ToV8(isolate, "update")).ToLocalChecked();
            if (f.IsEmpty() || !f->IsFunction()) return false;
            auto d = v8b::ToV8(isolate, delta).As<Value>();
            f.As<Function>()->Call(context, sw_object, 1, &d);

            return true;
        });

        sw::Renderer::Uninit();

        v8b::ClassManagerPool::RemoveAll(isolate);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
}