/**
 * VERTEX.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef VERTEX
#define VERTEX

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Color.hpp"


namespace Fireside::Rendering 
{
  struct Vertex 
  {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec2 _uv): 
      pos(_pos), normal(_normal), uv(_uv) { }
  };
}

#endif