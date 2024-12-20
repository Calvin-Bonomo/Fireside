/**
 * DRAWLIST.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "DrawList.hpp"

Fireside::Rendering::DrawCall::DrawCall(
  unsigned int vaoIndex, 
  unsigned int count, 
  glm::mat4 modelMatrix, 
  Program* pProgram,
  uniform_func uFunc,
  void* arg):
  vaoIndex(vaoIndex),
  count(count),
  modelMatrix(modelMatrix),
  uFunc(uFunc),
  arg(arg) 
  {
    this->pProgram = pProgram;
  }

Fireside::Rendering::DrawCall::DrawCall():
  vaoIndex(0),
  count(0),
  modelMatrix(0),
  uFunc(nullptr) { }

Fireside::Rendering::DrawList::DrawList(unsigned int size) 
{
  m_DrawCalls = new DrawCall[size];
  m_MaxSize = size;
  m_End = 0;
  m_Current = 0;
}

Fireside::Rendering::DrawList::~DrawList() 
{
  Clear();
  delete m_DrawCalls;
}

void Fireside::Rendering::DrawList::Reset() 
{
  m_Current = 0;
}

void Fireside::Rendering::DrawList::Clear() 
{
  for (auto& val : *this) 
    free(val.arg);
  m_Current = 0;
  m_End = 0;
}

Fireside::Rendering::DrawCall* Fireside::Rendering::DrawList::begin() const
{
  return m_DrawCalls;
}

Fireside::Rendering::DrawCall* Fireside::Rendering::DrawList::end() const
{
  return m_DrawCalls + m_End;
}

bool Fireside::Rendering::DrawList::Append(DrawCall call) 
{
  if (m_End == m_MaxSize)
    return false;
  
  m_DrawCalls[m_End++] = call;
  return true;
}