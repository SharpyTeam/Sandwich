//
// Created by selya on 31.08.2019.
//

#ifndef SANDWICH_GL_HPP
#define SANDWICH_GL_HPP

#if TARGET_ANDROID
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#elif TARGET_IOS
#include <OpenGLES/ES2/gl.h>
#elif TARGET_DESKTOP
#ifdef TARGET_WINDOWS
#include <Windows.h>
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#endif //SANDWICH_GL_HPP
