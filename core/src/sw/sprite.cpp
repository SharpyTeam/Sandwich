//
// Created by selya on 23.07.2019.
//

#include <sw/sprite.hpp>

#include <v8.h>

namespace sw {

template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Sprite>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto sprite = new Sprite;
                sprite->position.Wrap();
                sprite->scale.Wrap();
                info.This()->SetAlignedPointerInInternalField(0, sprite);
            }
    );

    function_template->SetClassName(v8_str("Sprite"));

    function_template->InstanceTemplate()->SetInternalFieldCount(1);

    auto o_template = function_template->InstanceTemplate();

    o_template->SetAccessor(
            v8_str("position"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto s = ObjectWrap::Unwrap<Sprite>(info.Holder());
                info.GetReturnValue().Set(s->position.GetHandle());
            },
            nullptr,
            v8::Local<v8::Value>(),
            v8::AccessControl::DEFAULT,
            (v8::PropertyAttribute)(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly)t
    );

    o_template->SetAccessor(
            v8_str("scale"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto s = ObjectWrap::Unwrap<Sprite>(info.Holder());
                info.GetReturnValue().Set(s->scale.GetHandle());
            },
            nullptr,
            v8::Local<v8::Value>(),
            v8::AccessControl::DEFAULT,
            (v8::PropertyAttribute)(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly)
    );

    o_template->SetAccessor(
            v8_str("rotation"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto s = ObjectWrap::Unwrap<Sprite>(info.Holder());
                info.GetReturnValue().Set(s->rotation);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto s = ObjectWrap::Unwrap<Sprite>(info.Holder());
                s->rotation = value.As<v8::Number>()->Value();
            }
    );

    return function_template;
}

DEFINE_WRAP(Sprite)

}