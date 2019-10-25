//
// Created by selya on 25.10.2019.
//

#include "screen.hpp"

#include "gl.hpp"

#include <iostream>

namespace sw {

void *Screen::window = nullptr;
int Screen::width = 0;
int Screen::height = 0;

Screen::ScreenMode Screen::GetMode() {
    return ScreenMode::BORDERLESS_WINDOW;
}

void Screen::SetMode(Screen::ScreenMode screen_mode, int refresh_rate) {
    int xpos, ypos;
    glfwGetWindowPos((GLFWwindow *)window, &xpos, &ypos);
    switch (screen_mode) {
        case ScreenMode::WINDOWED: {
            glfwSetWindowMonitor((GLFWwindow *)window, nullptr,
                                 xpos, ypos, width, height,
                                 refresh_rate ? refresh_rate : GLFW_DONT_CARE);
            break;
        }
        case ScreenMode::FULLSCREEN: {
            glfwSetWindowMonitor((GLFWwindow *)window, glfwGetPrimaryMonitor(),
                                 xpos, ypos, width, height,
                                 refresh_rate ? refresh_rate : GLFW_DONT_CARE);
            break;
        }
        case ScreenMode::BORDERLESS_WINDOW: {
            throw std::runtime_error("Borderless window is not supported yet");
        }
    }
}

int Screen::GetWidth() {
    return width;
}

int Screen::GetHeight() {
    return height;
}

void Screen::SetResolution(int width_, int height_) {
    if (!window) return;
    glfwSetWindowSize((GLFWwindow *)window, width_, height_);
    width = width_;
    height = height_;
}

void Screen::SetResolution(int width_, int height_, Screen::ScreenMode screen_mode, int refresh_rate) {
    SetResolution(width_, height_);
    SetMode(screen_mode, refresh_rate);
}

std::vector<Screen::Resolution> Screen::GetSupportedFullscreenResolutions() {
    int count;
    const GLFWvidmode *mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
    std::vector<Screen::Resolution> modes;
    for (int i = 0; i < count; ++i) {
        modes.emplace_back(Resolution {
            mode->width,
            mode->height,
            mode->refreshRate
        });
        mode++;
    }
    return modes;
}

bool Screen::Init() {
    glfwSetErrorCallback([](int id, const char *description) {
        std::cerr << description << std::endl;
    });

    if (!glfwInit()) {
        return false;
    }

    width = 640;
    height = 480;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, "sw", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent((GLFWwindow *)window);
    glfwSwapInterval(0);
}

void Screen::Uninit() {
    if (!window) return;
    glfwDestroyWindow((GLFWwindow *)window);
    glfwTerminate();
}

} //namespace sw
