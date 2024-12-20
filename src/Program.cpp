/**
 * PROGRAM.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "Rendering/Program.hpp"


Fireside::Rendering::Program::Program() 
{
  m_ProgramIndex = glCreateProgram();
  CheckError();
}

Fireside::Rendering::Program::~Program() 
{
  if (m_ProgramIndex != 0)
  {
    glDeleteProgram(m_ProgramIndex);
    CheckError();
  }
}

void Fireside::Rendering::Program::AttachShader(Shader& shader) 
{
  glAttachShader(m_ProgramIndex, shader.shaderIndex);
  CheckError();
}

void Fireside::Rendering::Program::Link() 
{
  glLinkProgram(m_ProgramIndex);
  CheckError();

  GLint status;
  glGetProgramiv(m_ProgramIndex, GL_LINK_STATUS, &status);
  CheckError();
  if (status != GL_TRUE) 
  {
    glGetProgramiv(m_ProgramIndex, GL_INFO_LOG_LENGTH, &status);
    CheckError();
    char* log = new char[status + 1];
    glGetProgramInfoLog(m_ProgramIndex, status, NULL, log);
    CheckError();
    Util::LogError("Unable to link program!\n%s\n", log);
  }
}

void Fireside::Rendering::Program::UseProgram() 
{
  glUseProgram(m_ProgramIndex);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, int value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::int1);
  if (loc == -1)
    Util::LogError("Invalid uniform, %s!\n", uniformName.c_str());

  glUniform1i(loc, value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, unsigned int value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::uint1);
  if (loc == -1)
    Util::LogError("Invalid uniform, %s!\n", uniformName.c_str());

  glUniform1ui(loc, value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, float value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::float1);
  if (loc == -1)
    Util::LogError("Invalid uniform, %s!\n", uniformName.c_str());
  
  glUniform1f(loc, value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, glm::vec2 value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::float2);
  if (loc == -1)
    Util::LogError("Invalid uniform, %s!\n", uniformName.c_str());
  
  glUniform2fv(loc, 1, (float*)&value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, glm::vec3 value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::float3);
  if (loc == -1)
    Util::LogError("Invalid uniform type for, %s!\n", uniformName.c_str());
  
  glUniform3fv(loc, 1, (float*)&value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, glm::vec4 value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::float4);
  if (loc == -1)
    Util::LogError("Invalid uniform type for, %s!\n", uniformName.c_str());
  
  glUniform4fv(loc, 1, (float*)&value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniform(std::string uniformName, glm::mat4 value) 
{
  int loc = GetUniform(uniformName.c_str(), UniformType::matrix4x4);
  if (loc == -1)
    Util::LogError("Invalid uniform for, %s!\n", uniformName.c_str());
  
  glUniformMatrix4fv(loc, 1, GL_FALSE, (float*)&value);
  CheckError();
}

void Fireside::Rendering::Program::SetUniformBlock(
  std::string blockName, 
  Fireside::Rendering::UniformBufferObject& ubo) 
{
  unsigned int binding = GetUniformBlockBinding(blockName.c_str());
  if (binding < 0)
    Util::LogError("Invalid binding, %s!\n", blockName.c_str());

  glUniformBlockBinding(m_ProgramIndex, binding, ubo.GetBinding());
  CheckError();
}

int Fireside::Rendering::Program::GetUniform(const char* uniformName, UniformType type) 
{
  if (auto find = m_Uniforms.find(uniformName); find != m_Uniforms.end()) 
    return find->second.type == type? find->second.loc : -1;

  int loc = glGetUniformLocation(m_ProgramIndex, uniformName);
  CheckError();

  if (loc >= 0)
    m_Uniforms[uniformName] = { type, loc };
  else
    Util::LogError("Unable to bind uniform %s @ %d.\n", uniformName, loc);
  return loc;
}

unsigned int Fireside::Rendering::Program::GetUniformBlockBinding(const char* blockName) 
{
  if (auto find = m_UniformBlocks.find(blockName); find != m_UniformBlocks.end())
    return find->second;
  
  unsigned int binding = glGetUniformBlockIndex(m_ProgramIndex, blockName);
  CheckError();

  if (binding < 0)
    m_UniformBlocks[blockName] = binding;
  return binding;
}
