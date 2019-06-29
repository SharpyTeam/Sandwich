#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <filesystem>
#include <libplatform/libplatform.h>
#include <v8.h>

extern "C" const char js_bundle_contents[];

using namespace v8;

#define v8_str(s) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), s).ToLocalChecked()

/*template<class F>
void SetWeak(const v8::Local<v8::Object> &o, F function) {
    struct SetWeakCallbackData {
        SetWeakCallbackData(const v8::Local<v8::Object> &o, F function) : function(function) {
            this->global.Reset(Isolate::GetCurrent(), o);
        }
        F function;
        v8::Global<v8::Object> global;
    };

    auto callback_data = new SetWeakCallbackData(o, function);

    callback_data->global.SetWeak(
            callback_data,
            [](const v8::WeakCallbackInfo<SetWeakCallbackData> &data) {
                SetWeakCallbackData *callback_data = data.GetParameter();
                callback_data->function(callback_data->global.Get(Isolate::GetCurrent()));
                callback_data->global.Reset();
                delete callback_data;
            }, v8::WeakCallbackType::kParameter
    );
}*/

class Vector2 {
public:
    double x;
    double y;

    Vector2() : x(0.0), y(0.0) {}
    Vector2(double scalar) : x(scalar), y(scalar) {}
    Vector2(double x, double y) : x(x), y(y) {}
    Vector2(const Vector2 &other) : x(other.x), y(other.y) {}

    Vector2 &Set(double scalar) {
        x = scalar;
        y = scalar;
        return *this;
    }
};

template<class T>
Local<FunctionTemplate> &GetObjectConstructorTemplate();


template<>
Local<FunctionTemplate> &GetObjectConstructorTemplate<Vector2>() {
    static Local<FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = FunctionTemplate::New(
            Isolate::GetCurrent(),
            [](const FunctionCallbackInfo<Value> &info) {
                Vector2 *v = nullptr;
                if (info.Length() == 1 && info[0]->IsObject()) {
                    v = new Vector2(
                            *(Vector2 *)info[0].As<Object>()->GetInternalField(
                                    0).As<External>()->Value());
                } else {
                    switch (info.Length()) {
                        case 0:
                            v = new Vector2();
                            break;
                        case 1:
                            v = new Vector2(info[0].As<Number>()->Value());
                            break;
                        case 2:
                            v = new Vector2(info[0].As<Number>()->Value(),
                                            info[1].As<Number>()->Value());
                            break;
                    }
                }

                Isolate::GetCurrent()->AdjustAmountOfExternalAllocatedMemory(sizeof(Vector2));

                info.This()->SetInternalField(0, External::New(info.GetIsolate(), v));

                /*SetWeak(info.This(), [](Local<Object> o) {
                    std::cout << o->GetInternalField(0).As<External>()->Value() << std::endl;
                    delete (Vector2 *)o->GetInternalField(0).As<External>()->Value();
                    Isolate::GetCurrent()->AdjustAmountOfExternalAllocatedMemory(-sizeof(Vector2));
                });*/
            }
    );

    function_template->SetClassName(v8_str("Vector2"));

    function_template->InstanceTemplate()->SetInternalFieldCount(1);

    auto o_template = function_template->InstanceTemplate();

    o_template->SetAccessor(
            v8_str("x"),
            [](Local<String> property, const PropertyCallbackInfo<Value> &info) {
                auto *v = (Vector2 *)info.Holder()->GetInternalField(0).As<External>()->Value();
                info.GetReturnValue().Set(v->x);
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](Local<String> property, const PropertyCallbackInfo<Value> &info) {
                auto *v = (Vector2 *)info.Holder()->GetInternalField(0).As<External>()->Value();
                info.GetReturnValue().Set(v->y);
            }
    );

    o_template->Set(
            v8_str("set"),
            FunctionTemplate::New(Isolate::GetCurrent(), [](const FunctionCallbackInfo<Value> &info) {
                auto *v = (Vector2 *)info.Holder()->GetInternalField(0).As<External>()->Value();
                v->Set(info[0].As<Number>()->Value());
                info.GetReturnValue().Set(info.Holder());
            })
    );

    return function_template;
}

/*template<class T>
Persistent<Object> Wrap(void *ptr) {
    Local<Object> o = GetObjectTemplate<T>()->NewInstance(Isolate::GetCurrent()->GetCurrentContext()).ToLocalChecked();
    o->SetInternalField(0, External::New(Isolate::GetCurrent(), ptr));
    return Persistent<Object>(Isolate::GetCurrent(), o);
}*/

int main(int argc, char *argv[]) {
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

        sw_object->Set(String::NewFromUtf8(isolate, "Vector2").ToLocalChecked(),
                       GetObjectConstructorTemplate<Vector2>()->GetFunction(context).ToLocalChecked());


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

        if (t.HasCaught()) {
            std::cerr << *String::Utf8Value(Isolate::GetCurrent(), t.Exception()) << std::endl;
        }
    }



    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
}