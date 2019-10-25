//
// Created by selya on 26.09.2019.
//

#ifndef SANDWICH_RENDERER_RENDERER_HPP
#define SANDWICH_RENDERER_RENDERER_HPP

#include "gl.hpp"
#include "sprite_batch.hpp"
#include "screen.hpp"

#include <iostream>

namespace sw {

class Renderer {
public:
    static inline void Init() {
        Screen::Init();

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
        while (!glfwWindowShouldClose((GLFWwindow *)Screen::window)) {
            glViewport(0, 0, Screen::GetWidth(), Screen::GetHeight());

            glClearColor(0.5, 0.5, 0.5, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!update_function()) break;

            glfwSwapBuffers((GLFWwindow *)Screen::window);
            glfwPollEvents();
        }

    }

    static inline void Uninit() {
        Screen::Uninit();
    }
};

} // namespace sw

#endif //SANDWICH_RENDERER_RENDERER_HPP
