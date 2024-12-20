/**
 * VERTEXARRAYOBJECT.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef VERTEX_ARRAY_OBJECT
#define VERTEX_ARRAY_OBJECT

#include "config.hpp"
#include "Rendering/Vertex.hpp"


namespace Fireside::Rendering
{
  struct VertexArrayObject 
  {
    GLuint vaoIndex;
    GLuint vboIndex;
    GLuint eaoIndex;
    Vertex* vertices;
    unsigned int vertexCount;
    unsigned int* elements;
    unsigned int elementCount;

    VertexArrayObject(Vertex* _vertices, unsigned int _vertexCount, unsigned int* _elements, unsigned int _elementCount):
      vaoIndex(0),
      vboIndex(0), 
      eaoIndex(0),
      vertices(_vertices),
      vertexCount(_vertexCount),
      elements(_elements),
      elementCount(_elementCount) { }
  };

  int CreateVAO(VertexArrayObject& vao);
  void DeleteVAO(VertexArrayObject& vao);

  void BindVAO(VertexArrayObject& vao);
  void UnbindVAO(VertexArrayObject& vao);
}

#endif