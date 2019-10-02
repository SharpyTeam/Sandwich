#include <sw/modules/math.hpp>

#include <v8bind/v8bind.hpp>

#include <libplatform/libplatform.h>
#include <v8.h>

#include <iostream>
#include <chrono>
#include <sw/test/std_calculator.hpp>

#include <sw/gl.hpp>
#include <sw/sprite_batch.hpp>

#include <sw/scene_node.hpp>
#include <sw/scene.hpp>

extern "C" const char js_bundle_contents[];

using namespace v8;

void Start() {
    //putenv("DISPLAY=:0");

    glfwSetErrorCallback([](int id, const char *description) {
        std::cerr << description << std::endl;
    });

    if (!glfwInit()) {
        return;
    }

    int width = 640;
    int height = 480;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    auto window = glfwCreateWindow(width, height, "sw", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum glew_init_status = glewInit();

    if (glew_init_status != GLEW_OK) {
        return;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    {
        sw::SpriteBatch sb;
        sw::Matrix4 proj;
        proj.SetOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
        sb.SetProjectionMatrix(proj);
        auto data = sw::TextureData(100, 100);
        data.Fill(1, 0, 0, 1);
        auto texture = sw::Texture::Create(data);
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.5, 0.5, 0.5, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            sb.Begin();
            sb.Draw(texture, 0, 0);
            sb.End();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }


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

        auto scene =

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