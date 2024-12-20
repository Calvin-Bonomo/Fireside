/**
 * SHADER.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef SHADER
#define SHADER

#include <string>

#include "config.hpp"


namespace Fireside::Rendering
{
  struct Shader 
  {
    unsigned int shaderIndex;
    GLenum type;
    const char* sourceCode;
  };

  int CreateShader(Shader& shader);
  void DeleteShader(Shader& shader);
}

#endif