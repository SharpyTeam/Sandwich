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
        r.PointerAutoWrap();

        v8b::Class<sw::Screen::ScreenMode> sm(isolate);
        sm.StaticConst("WINDOWED", sw::Screen::ScreenMode::WINDOWED);
        sm.StaticConst("FULLSCREEN", sw::Screen::ScreenMode::FULLSCREEN);
        sm.StaticConst("BORDERLESS_WINDOW", sw::Screen::ScreenMode::BORDERLESS_WINDOW);

        v8b::Class<sw::Screen> s(isolate);

        s.InnerClass("ScreenMode", sm);
        s.InnerClass("Resolution", r);

        s.StaticProperty("width", &sw::Screen::GetWidth);
        s.StaticProperty("height", &sw::Screen::GetHeight);
        s.StaticProperty("mode", &sw::Screen::GetMode, [](sw::Screen::ScreenMode mode) {
            sw::Screen::SetMode(mode);
        });
        s.StaticFunction("getTitle", &sw::Screen::GetTitle);
        s.StaticFunction("setTitle", &sw::Screen::SetTitle);
        s.StaticFunction("setMode", &sw::Screen::SetMode);
        s.StaticFunction<void (*)(int, int, sw::Screen::ScreenMode, int)>("setResolution", &sw::Screen::SetResolution);
        s.StaticFunction("getSupportedFullscreenResolutions", &sw::Screen::GetSupportedFullscreenResolutions);
    }
};

};

#endif //SANDWICH_BINDINGS_RENDERER_HPP
