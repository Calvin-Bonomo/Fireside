/**
 * SHADER.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "Rendering/Shader.hpp"

int Fireside::Rendering::CreateShader(Shader& shader)
{ 
  shader.shaderIndex = glCreateShader(shader.type);
  CheckError();
  glShaderSource(shader.shaderIndex, 1, &shader.sourceCode, NULL);
  CheckError();
  glCompileShader(shader.shaderIndex);
  CheckError();
  int success;
  glGetShaderiv(shader.shaderIndex, GL_COMPILE_STATUS, &success);
  CheckError();
  if (!success) 
  {
    GLint length;
    glGetShaderiv(shader.shaderIndex, GL_INFO_LOG_LENGTH, &length);
    CheckError();
    GLchar *pInfo = new GLchar[length + 1];
    glGetShaderInfoLog(shader.shaderIndex, length, NULL, pInfo);
    CheckError();
    fprintf(stderr, "Unable to compile shader!\n%s\n", pInfo);
    delete[] pInfo;
    return 0;
  }
  return 1;
}

void Fireside::Rendering::DeleteShader(Shader& shader) 
{
  glDeleteShader(shader.shaderIndex);
  CheckError();
}
