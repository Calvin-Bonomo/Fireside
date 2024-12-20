/**
 * VERTEXARRAYOBJECT.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "Rendering/VertexArrayObject.hpp"

int Fireside::Rendering::CreateVAO(VertexArrayObject& vao) 
{
  if (vao.vertexCount == 0 || vao.vertices == nullptr)
    return 0;

  glGenBuffers(1, &vao.vboIndex);
  CheckError();
  glBindBuffer(GL_ARRAY_BUFFER, vao.vboIndex);
  CheckError();
  glBufferData(GL_ARRAY_BUFFER, vao.vertexCount * sizeof(Vertex), vao.vertices, GL_STATIC_DRAW);
  CheckError();

  glGenVertexArrays(1, &vao.vaoIndex);
  CheckError();
  BindVAO(vao);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
  CheckError();
  glEnableVertexAttribArray(0);
  CheckError();
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
  CheckError();
  glEnableVertexAttribArray(1);
  CheckError();
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
  CheckError();
  glEnableVertexAttribArray(2);
  CheckError();

  if (vao.elementCount == 0 || vao.elements == nullptr)
  {
    glCreateBuffers(1, &vao.eaoIndex);
    CheckError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao.eaoIndex);
    CheckError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vao.elementCount * sizeof(unsigned int), vao.elements, GL_STATIC_DRAW);
    CheckError();
  }
  else vao.elementCount = vao.vertexCount;
  UnbindVAO(vao);
  return 1;
}

void Fireside::Rendering::DeleteVAO(VertexArrayObject& vao) 
{
  glDeleteBuffers(2, &vao.vboIndex);
  CheckError();
  glDeleteVertexArrays(1, &vao.vaoIndex);
  CheckError();
}

void Fireside::Rendering::BindVAO(VertexArrayObject& vao) 
{
  glBindVertexArray(vao.vaoIndex);
  CheckError();
}

void Fireside::Rendering::UnbindVAO(VertexArrayObject& vao) 
{
  glBindVertexArray(0);
  CheckError();
}