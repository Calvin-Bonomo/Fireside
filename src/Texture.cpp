/**
 * TEXTURE.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "Rendering/Texture.hpp"

void Fireside::Rendering::CreateTexture(Texture& texture, bool keepData) 
{
  glGenTextures(1, &texture.textureIndex);
  CheckError();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_FLOAT, texture.buffer);
  CheckError();
  if (!keepData)
    delete texture.buffer;
}

void Fireside::Rendering::DeleteTexture(Texture& texture) 
{
  glDeleteTextures(1, &texture.textureIndex);
  CheckError();
}