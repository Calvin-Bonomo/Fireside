/**
 * PROGRAM.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef PROGRAM
#define PROGRAM

#include <map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Rendering/Shader.hpp"
#include "Rendering/UniformBufferObject.hpp"
#include "Util/Log.hpp"


namespace Fireside::Rendering
{ 
  class Program
  {
  private:
    enum class UniformType 
    {
      float1, float2, float3, float4,
      int1, int2, int3, int4,
      uint1, uint2, uint3, uint4,
      matrix2x2, matrix3x3, matrix4x4,
      matrix2x3, matrix3x2,
      matrix2x4, matrix4x2,
      matrix3x4, matrix4x3
    };

    struct Uniform 
    {
      UniformType type;
      int loc;
    };
  private:
    unsigned int m_ProgramIndex;
    std::map<const char*, Uniform> m_Uniforms;
    std::map<const char*, unsigned int> m_UniformBlocks;
  public:
    Program();
    ~Program();

    void AttachShader(Shader& shader);
    void Link();
    void UseProgram();

    void SetUniform(std::string uniformName, int value);
    
    void SetUniform(std::string uniformName, unsigned int value);

    void SetUniform(std::string uniformName, float value);
    void SetUniform(std::string uniformName, glm::vec2 value);
    void SetUniform(std::string uniformName, glm::vec3 value);
    void SetUniform(std::string uniformName, glm::vec4 value);

    void SetUniform(std::string uniformName, glm::mat4 value);

    void SetUniformBlock(std::string blockName, UniformBufferObject& ubo);
  private:
    int GetUniform(const char* uniformName, UniformType type);
    unsigned int GetUniformBlockBinding(const char* blockName);
  };
}

#endif