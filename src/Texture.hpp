/**
 * TEXTURE.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef TEXTURE
#define TEXTURE

#include "Color.hpp"


namespace Fireside::Rendering 
{
  struct Texture 
  {
    GLuint textureIndex;
    unsigned int width, height, levels;
    Color* buffer;
  };

  void CreateTexture(Texture& texture, bool keepData = false);
  void DeleteTexture(Texture& texture);
}

#endif