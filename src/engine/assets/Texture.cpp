#include <GL/glew.h>

#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../system/logger.h"
#include "stb_image.h"

#define ID "texture"

Texture::Texture(std::string path) {
  unsigned int texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

  if (data) {
    GLenum format = GL_NONE;
    if (nrChannels == 1)
      format = GL_RED;
    else if (nrChannels == 3)
      format = GL_RGB;
    else if (nrChannels == 4)
      format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    loggerInfo(ID, "Loaded texture from path '%s'", path.c_str());
    this->id = texture;
  } else {
    loggerError(ID, "Texture failed to load at path: %s", path.c_str());
  }

  stbi_image_free(data);

  this->path = path;
}
