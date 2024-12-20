/**
 * DRAWLIST.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef DRAW_LIST
#define DRAW_LIST

#include <glm/mat4x4.hpp>

#include "Rendering/VertexArrayObject.hpp"
#include "Rendering/Program.hpp"

#include "config.hpp"

namespace Fireside::Rendering
{
  typedef void (*uniform_func)(Rendering::Program*, void*);

  struct DrawCall
  {    
    // VAO data
    unsigned int vaoIndex;
    unsigned int count;

    // Rendering Data
    glm::mat4 modelMatrix;
    Program* pProgram;
    uniform_func uFunc;
    void* arg;

    DrawCall(
      unsigned int vaoIndex, 
      unsigned int count, 
      glm::mat4 modelMatrix, 
      Program* pProgram,
      uniform_func uFunc,
      void* arg);
    DrawCall();
  };

  class DrawList 
  {
  private:
    unsigned int m_MaxSize,
      m_End,
      m_Current;
    DrawCall* m_DrawCalls;

  public:
    DrawList(unsigned int size);
    ~DrawList();

    void Reset();
    void Clear();

    bool Append(DrawCall call);

    DrawCall* begin() const;
    DrawCall* end() const;
  };
}

#endif