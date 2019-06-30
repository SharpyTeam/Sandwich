#include <utility>

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <filesystem>
#include <libplatform/libplatform.h>
#include <v8.h>
#include <functional>
#include "object_wrap.hpp"

extern "C" const char js_bundle_contents[];

using namespace v8;

#define v8_str(s) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), s).ToLocalChecked()

void SetWeak(const v8::Local<v8::Object> &o, std::function<void(Local<Object>)> f) {
    struct SetWeakCallbackData {
        SetWeakCallbackData(const v8::Local<v8::Object> &o, std::function<void(Local<Object>)> f) : function(std::move(f)) {
            this->persistent.Reset(Isolate::GetCurrent(), o);
        }
        std::function<void(Local<Object>)> function;
        Persistent<Object> persistent;
    };

    auto callback_data = new SetWeakCallbackData(o, std::move(f));

    callback_data->persistent.SetWeak(
            callback_data,
            [](const WeakCallbackInfo<SetWeakCallbackData> &data) {
                SetWeakCallbackData *callback_data = data.GetParameter();
                callback_data->function(callback_data->persistent.Get(Isolate::GetCurrent()));
                callback_data->persistent.Reset();
                delete callback_data;
            }, WeakCallbackType::kFinalizer
    );
}

template<int L>
class Vector;

template<>
class Vector<2> : public sw::ObjectWrap {
public:
    double x;
    double y;

    Vector<2>() : x(0.0), y(0.0) {}
    Vector<2>(double scalar) : x(scalar), y(scalar) {}
    Vector<2>(double x, double y) : x(x), y(y) {}
    Vector<2>(const Vector<2> &other) : x(other.x), y(other.y) {}

    Vector<2> &Set(double scalar) {
        x = scalar;
        y = scalar;
        return *this;
    }

    Local<FunctionTemplate> GetObjectConstructorTemplate() override {
        static Local<FunctionTemplate> function_template;
        if (!function_template.IsEmpty()) return function_template;

        // Constructor
        function_template = FunctionTemplate::New(
                Isolate::GetCurrent(),
                [](const FunctionCallbackInfo<Value> &info) {
                    Vector<2> *v = nullptr;
                    if (info.Length() == 1 && info[0]->IsObject()) {
                        v = new Vector<2>(*ObjectWrap::Unwrap<Vector<2>>(info[0].As<Object>()));
                    } else {
                        switch (info.Length()) {
                            case 0:
                                v = new Vector<2>();
                                break;
                            case 1:
                                v = new Vector<2>(info[0].As<Number>()->Value());
                                break;
                            case 2:
                                v = new Vector<2>(info[0].As<Number>()->Value(),
                                                  info[1].As<Number>()->Value());
                                break;
                        }
                    }

                    info.This()->SetAlignedPointerInInternalField(0, v);
                }
        );

        function_template->SetClassName(v8_str("Vector2"));

        function_template->InstanceTemplate()->SetInternalFieldCount(1);

        auto o_template = function_template->InstanceTemplate();

        o_template->SetAccessor(
                v8_str("x"),
                [](Local<String> property, const PropertyCallbackInfo<Value> &info) {
                    auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                    info.GetReturnValue().Set(v->x);
                },
                [](Local<String> property, Local<Value> value, const PropertyCallbackInfo<void> &info) {
                    auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                    v->x = value.As<Number>()->Value();
                }
        );

        o_template->SetAccessor(
                v8_str("y"),
                [](Local<String> property, const PropertyCallbackInfo<Value> &info) {
                    auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                    info.GetReturnValue().Set(v->y);
                },
                [](Local<String> property, Local<Value> value, const PropertyCallbackInfo<void> &info) {
                    auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                    v->y = value.As<Number>()->Value();
                }
        );

        o_template->Set(
                v8_str("set"),
                FunctionTemplate::New(Isolate::GetCurrent(), [](const FunctionCallbackInfo<Value> &info) {
                    auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                    v->Set(info[0].As<Number>()->Value());
                    info.GetReturnValue().Set(info.Holder());
                })
        );

        return function_template;
    }
};

typedef Vector<2> Vector2;


/*template<class T>
Persistent<Object> Wrap(T *ptr) {
    Local<Object> o = GetObjectConstructorTemplate<T>()->InstanceTemplate()->NewInstance(
            Isolate::GetCurrent()->GetCurrentContext());
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

        auto v = new Vector2;
        v->x = 131;
        v->Wrap();

        sw_object->Set(String::NewFromUtf8(isolate, "Vector2").ToLocalChecked(),
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

        std::cout << v->x << std::endl;

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