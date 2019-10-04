//
// Created by selya on 26.09.2019.
//

#ifndef SANDWICH_RENDERER_RENDERER_HPP
#define SANDWICH_RENDERER_RENDERER_HPP

#include "gl.hpp"
#include "sprite_batch.hpp"

#include <iostream>

namespace sw {

class Renderer {
    static inline int width;
    static inline int height;
    static inline GLFWwindow *window;

public:
    static inline void Init() {
        glfwSetErrorCallback([](int id, const char *description) {
            std::cerr << description << std::endl;
        });

        if (!glfwInit()) {
            return;
        }

        width = 640;
        height = 480;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(width, height, "sw", nullptr, nullptr);
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
    }

    template<typename F>
    static inline void Loop(F&& update_function) {
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.5, 0.5, 0.5, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!update_function()) break;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    static inline void Uninit() {
        glfwTerminate();
    }
};

} // namespace sw

#endif //SANDWICH_RENDERER_RENDERER_HPP
