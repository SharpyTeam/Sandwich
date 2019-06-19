#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <filesystem>
#include <libplatform/libplatform.h>
#include <v8.h>

using namespace v8;

class ModuleWrapper {
    Global<Module> module;

public:
    ModuleWrapper() {}

private:
    ModuleWrapper(const std::string &path, const std::string &text) {
        ScriptCompiler::Source source(String::NewFromUtf8(Isolate::GetCurrent(), text.c_str()).ToLocalChecked(),
                                      ScriptOrigin(
                                              String::NewFromUtf8(Isolate::GetCurrent(), path.c_str()).ToLocalChecked(),
                                              Local<v8::Integer>(), Local<v8::Integer>(),
                                              Local<v8::Boolean>(), Local<v8::Integer>(),
                                              Local<v8::Value>(), Local<v8::Boolean>(),
                                              Local<v8::Boolean>(), True(Isolate::GetCurrent())));

        module = Global<Module>(Isolate::GetCurrent(),
                                ScriptCompiler::CompileModule(Isolate::GetCurrent(), &source).ToLocalChecked());
    }

    static ModuleWrapper *GetModule(const std::string &path) {
        static std::map<std::string, ModuleWrapper> modules;
        std::string full_path = std::filesystem::canonical(std::filesystem::path(path)).string();
        if (modules.find(full_path) != modules.end()) {
            return &modules[full_path];
        }
        std::ifstream f(full_path);
        if (!f.good()) return nullptr;
        std::string str((std::istreambuf_iterator<char>(f)),
                        std::istreambuf_iterator<char>());
        modules[full_path] = ModuleWrapper(full_path, str);
        GetModulePaths()[modules[full_path].module.Get(Isolate::GetCurrent())->GetIdentityHash()] = full_path;
        return &modules[full_path];
    }

    static std::map<int, std::string> &GetModulePaths() {
        static std::map<int, std::string> paths;
        return paths;
    }

    static MaybeLocal<Module> ResolveCallback(Local<Context> context,
                                              Local<String> specifier,
                                              Local<Module> referrer) {
        auto referrer_path = GetModulePaths()[referrer->GetIdentityHash()];
        Isolate *isolate = Isolate::GetCurrent();
        ModuleWrapper *mw = GetModule(
                (std::filesystem::path(referrer_path).parent_path() /
                 std::filesystem::path(*String::Utf8Value(isolate, specifier))).string());
        if (mw) {
            return mw->module.Get(isolate);
        }
        return MaybeLocal<Module>();
    }

public:
    static MaybeLocal<Module> InstantiateModule(const std::string &path) {
        ModuleWrapper *mw = GetModule(path);
        if (!mw) return MaybeLocal<Module>();
        if (mw->module.Get(Isolate::GetCurrent())->InstantiateModule(Isolate::GetCurrent()->GetCurrentContext(),
                                                                     ResolveCallback).IsNothing())
            return MaybeLocal<Module>();
        return mw->module.Get(Isolate::GetCurrent());
    }
};

Global<Object> sw_object;

int main(int argc, char *argv[]) {
    // Initialize V8.
    V8::InitializeICUDefaultLocation(argv[0]);
    V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();
    V8::InitializePlatform(platform.get());
    V8::Initialize();

    // Create a new Isolate and make it the current one.
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
            ArrayBuffer::Allocator::NewDefaultAllocator();
    Isolate *isolate = Isolate::New(create_params);

    {
        Isolate::Scope isolate_scope(isolate);
        // Create a stack-allocated handle scope.
        HandleScope handle_scope(isolate);


        Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
        global->SetAccessor(String::NewFromUtf8(isolate, "sw").ToLocalChecked(), [](auto property, auto info) {
            info.GetReturnValue().Set(sw_object.Get(Isolate::GetCurrent()));
        });

        // Create a new context.
        Local<Context> context = Context::New(isolate, nullptr, global);
        // Enter the context for compiling and running the hello world script.
        Context::Scope context_scope(context);

        context->Global()->Get(String::NewFromUtf8(isolate, "console").ToLocalChecked())->ToObject(
                context).ToLocalChecked()->
                Set(String::NewFromUtf8(isolate, "log").ToLocalChecked(),
                    FunctionTemplate::New(isolate, [](auto info) {
                        String::Utf8Value utf8(info.GetIsolate(), info[0]);
                        std::cout << *utf8 << std::endl;
                    })->GetFunction(context).ToLocalChecked()
        );

        sw_object = Global<Object>(Isolate::GetCurrent(), Object::New(isolate));

        MaybeLocal<Value> result = ModuleWrapper::InstantiateModule("js/main.js").ToLocalChecked()->Evaluate(context);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
}