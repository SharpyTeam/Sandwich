//
// Created by Ilya on 29.08.2019.
//

#ifndef SANDWICH_BINDINGS_RENDERER_HPP
#define SANDWICH_BINDINGS_RENDERER_HPP

#include <v8bind/v8bind.hpp>

#include <sw/renderer/screen.hpp>

#include <iostream>

namespace v8b {

template<>
struct DefaultBindings<sw::Screen> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::Screen::Resolution> r(isolate);
        r.Var("width", &sw::Screen::Resolution::width);
        r.Var("height", &sw::Screen::Resolution::height);
        r.Var("refreshRate", &sw::Screen::Resolution::refresh_rate);

        r.AutoWrap();

        v8b::Class<sw::Screen::ScreenMode> sm(isolate);
        sm.StaticConst("Windowed", sw::Screen::ScreenMode::WINDOWED);
        sm.StaticConst("Fullscreen", sw::Screen::ScreenMode::FULLSCREEN);
        sm.StaticConst("BorderlessWindow", sw::Screen::ScreenMode::BORDERLESS_WINDOW);

        v8b::Class<sw::Screen> s(isolate);

        s.InnerClass("ScreenMode", sm);
        s.InnerClass("Resolution", r);

        s.StaticProperty("width", &sw::Screen::GetWidth);
        s.StaticProperty("height", &sw::Screen::GetHeight);
        s.StaticProperty("mode", &sw::Screen::GetMode, [](sw::Screen::ScreenMode mode) {
            sw::Screen::SetMode(mode);
        });
        s.StaticProperty("title", &sw::Screen::GetTitle, &sw::Screen::SetTitle);
        s.StaticFunction("setMode", &sw::Screen::SetMode);
        s.StaticFunction<
            void (*)(int, int),
            void (*)(int, int, sw::Screen::ScreenMode, int)>
            ("setResolution", &sw::Screen::SetResolution, &sw::Screen::SetResolution);
        s.StaticFunction("getSupportedFullscreenResolutions", &sw::Screen::GetSupportedFullscreenResolutions);
    }
};

template<>
struct DefaultBindings<sw::Shader> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::Shader::Stage> stage(isolate);
        stage.StaticConst("Vertex", sw::Shader::Stage::Vertex);
        stage.StaticConst("Fragment", sw::Shader::Stage::Fragment);
        stage.StaticConst("Geometry", sw::Shader::Stage::Geometry);

        v8b::Class<sw::Shader::ValueType> type(isolate);
        type.StaticConst("Float", sw::Shader::ValueType::FLOAT);
        type.StaticConst("Int", sw::Shader::ValueType::INT);
        type.StaticConst("UnsignedInt", sw::Shader::ValueType::UNSIGNED_INT);
        type.StaticConst("Matrix3Float", sw::Shader::ValueType::MATRIX_3_FLOAT);
        type.StaticConst("Matrix4Float", sw::Shader::ValueType::MATRIX_4_FLOAT);
        type.StaticConst("Vector2Float", sw::Shader::ValueType::VECTOR_2_FLOAT);
        type.StaticConst("Vector3Float", sw::Shader::ValueType::VECTOR_3_FLOAT);
        type.StaticConst("Vector4Float", sw::Shader::ValueType::VECTOR_4_FLOAT);
        type.StaticConst("Vector2Int", sw::Shader::ValueType::VECTOR_2_INT);
        type.StaticConst("Vector3Int", sw::Shader::ValueType::VECTOR_3_INT);
        type.StaticConst("Vector4Int", sw::Shader::ValueType::VECTOR_4_INT);
        type.StaticConst("Vector2UnsignedInt", sw::Shader::ValueType::VECTOR_2_UNSIGNED_INT);
        type.StaticConst("Vector3UnsignedInt", sw::Shader::ValueType::VECTOR_3_UNSIGNED_INT);
        type.StaticConst("Vector4UnsignedInt", sw::Shader::ValueType::VECTOR_4_UNSIGNED_INT);
        type.StaticConst("TextureUnit", sw::Shader::ValueType::TEXTURE_UNIT);
        type.StaticConst("Unsupported", sw::Shader::ValueType::UNSUPPORTED);

        v8b::Class<sw::Shader::Attribute> attribute(isolate);
        attribute.Var("name", &sw::Shader::Attribute::name);
        attribute.Var("type", &sw::Shader::Attribute::type);
        attribute.Var("location", &sw::Shader::Attribute::location);
        attribute.AutoWrap();

        v8b::Class<sw::Shader::Uniform> uniform(isolate);
        uniform.Var("name", &sw::Shader::Uniform::name);
        uniform.Var("type", &sw::Shader::Uniform::type);
        uniform.Var("location", &sw::Shader::Uniform::location);
        uniform.Function<
            void (sw::Shader::Uniform::*)(double),
            void (sw::Shader::Uniform::*)(const sw::math::Vector2 &),
            void (sw::Shader::Uniform::*)(const sw::math::Vector3 &),
            void (sw::Shader::Uniform::*)(const sw::math::Vector4 &),
            void (sw::Shader::Uniform::*)(const sw::math::Matrix4 &)>
            ("set", &sw::Shader::Uniform::Set, &sw::Shader::Uniform::Set,
                &sw::Shader::Uniform::Set, &sw::Shader::Uniform::Set, &sw::Shader::Uniform::Set);
        uniform.AutoWrap();

        v8b::Class<sw::Shader> s(isolate);

        s.InnerClass("Stage", stage);
        s.InnerClass("ValueType", type);
        s.InnerClass("Attribute", attribute);
        s.InnerClass("Uniform", uniform);

        s.Property("uniforms", &sw::Shader::GetUniforms);
        s.Property("attributes", &sw::Shader::GetAttributes);

        s.Function("getUniform", &sw::Shader::GetUniform);
        s.Function("getAttribute", &sw::Shader::GetAttribute);

        s.Function("bind", &sw::Shader::Bind);

        s.StaticFunction("fromSource", &sw::Shader::FromSource);

        s.AutoWrap();
    }
};

template<>
struct DefaultBindings<sw::SpriteBatch> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::SpriteBatch> sb(isolate);

        sb.Constructor<std::tuple<>>();

        sb.Property("color", &sw::SpriteBatch::GetColor, &sw::SpriteBatch::SetColor);
        sb.Property("shader", &sw::SpriteBatch::GetShader, &sw::SpriteBatch::SetShader);
        sb.Property("viewMatrix", &sw::SpriteBatch::GetViewMatrix, &sw::SpriteBatch::SetViewMatrix);
        sb.Property("projectionMatrix", &sw::SpriteBatch::GetProjectionMatrix, &sw::SpriteBatch::SetProjectionMatrix);

        sb.Function("begin", &sw::SpriteBatch::Begin);
        sb.Function("flush", &sw::SpriteBatch::Flush);
        sb.Function("end", &sw::SpriteBatch::End);

        sb.Function<
            void (sw::SpriteBatch::*)(const std::shared_ptr<sw::Texture> &,
                double, double, double, double, double, double, double, bool, bool),
            void (sw::SpriteBatch::*)(const sw::TextureRegion &,
                double, double, double, double, double, double, double, bool, bool),
            void (sw::SpriteBatch::*)(const sw::TextureRegion &,
                const sw::math::Vector2 &, double, const sw::math::Vector2 &,
                const sw::math::Vector2 &, bool, bool),
            void (sw::SpriteBatch::*)(const std::shared_ptr<sw::Texture> &,
                const sw::math::Vector2 &, double, const sw::math::Vector2 &,
                const sw::math::Vector2 &, bool, bool)>
            ("draw", &sw::SpriteBatch::Draw, &sw::SpriteBatch::Draw,
            &sw::SpriteBatch::Draw, &sw::SpriteBatch::Draw);

        sb.AutoWrap();
    }
};

/*template<>
struct DefaultBindings<sw::TextureData> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::TextureData> td(isolate);


    }
};*/

}

#endif //SANDWICH_BINDINGS_RENDERER_HPP
