/**
 * UNIFORMBUFFEROBJECT.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "Rendering/UniformBufferObject.hpp"

Fireside::Rendering::UniformBufferObject::UniformBufferObject(void* data, size_t size, unsigned int binding):
  m_BufferData(data),
  m_DataSize(size),
  m_Binding(binding)
{
  glGenBuffers(1, &m_BufferIndex);
  CheckError();
  Bind();
  glBufferData(GL_UNIFORM_BUFFER, m_DataSize, m_BufferData, GL_DYNAMIC_DRAW);
  CheckError();
  glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_BufferIndex);
  CheckError();
  Unbind();
}

Fireside::Rendering::UniformBufferObject::UniformBufferObject():
  m_BufferData(nullptr),
  m_DataSize(0),
  m_Binding(0) { }


Fireside::Rendering::UniformBufferObject::~UniformBufferObject() { }

void Fireside::Rendering::UniformBufferObject::Bind() 
{
  glBindBuffer(GL_UNIFORM_BUFFER, m_BufferIndex);
  CheckError();
}

void Fireside::Rendering::UniformBufferObject::Unbind() 
{
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  CheckError();
}

void Fireside::Rendering::UniformBufferObject::EditData(void* data, size_t offset, size_t size) 
{
  if (size == 0)
    size = m_DataSize;
  if (size + offset > m_DataSize)
    Util::LogError("Unable to set uniform buffer data @ %llu. Max size of %llu.", offset, m_DataSize);
  Bind();
  glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
  CheckError();
  Unbind();
}

unsigned int Fireside::Rendering::UniformBufferObject::GetBinding() 
{
  return m_Binding;
}

