#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLLogError(#x, __FILE__, __LINE__)) \


static void GLClearError() {
  while (glGetError() != GL_NO_ERROR);
}

static bool GLLogError(const char* fun_fn, const char* file_fn, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] ( " << error << " )" << std::endl;
    std::cout << fun_fn << "; " << file_fn << ":" << line << std::endl;
    return false;
  }
  return true;
}