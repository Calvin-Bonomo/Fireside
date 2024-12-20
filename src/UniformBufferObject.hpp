/**
 * UNIFORMBUFFEROBJECT.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef UNIFORM_BUFFER_OBJECT
#define UNIFORM_BUFFER_OBJECT

#include "config.hpp"
#include "Util/Log.hpp"


namespace Fireside::Rendering 
{
  class UniformBufferObject 
  {
  private:
    unsigned int m_BufferIndex;
    unsigned int m_Binding;
    size_t m_DataSize;
    void* m_BufferData;
  public:
    UniformBufferObject(void* data, size_t size, unsigned int binding);
    UniformBufferObject();
    ~UniformBufferObject();

    void Bind();
    void Unbind();

    void EditData(void* data, size_t offset = 0, size_t size = 0);

    unsigned int GetBinding();
  };
}

#endif