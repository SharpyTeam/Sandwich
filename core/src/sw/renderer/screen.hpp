//
// Created by selya on 25.10.2019.
//

#ifndef SANDWICH_RENDERER_SCREEN_HPP
#define SANDWICH_RENDERER_SCREEN_HPP

#include <vector>
#include <string>

namespace sw {

class Screen {
    friend class Renderer;

    static void *window;
    static int width;
    static int height;
    static std::string title;

public:
    struct Resolution {
        int width;
        int height;
        int refresh_rate;
    };

    enum class ScreenMode {
        WINDOWED,
        FULLSCREEN,
        BORDERLESS_WINDOW
    };

    static std::string GetTitle();
    static void SetTitle(const std::string &title);

    static ScreenMode GetMode();
    static void SetMode(ScreenMode screen_mode, int refresh_rate = 0);

    static int GetWidth();
    static int GetHeight();

    static void SetResolution(int width, int height);
    static void SetResolution(int width, int height, ScreenMode screen_mode, int refresh_rate = 0);

    static std::vector<Resolution> GetSupportedFullscreenResolutions();

private:
    static bool Init();
    static void Uninit();
};

} //namespace sw

#endif //SANDWICH_RENDERER_SCREEN_HPP
