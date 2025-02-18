#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Texture.hpp"
#include <glm/ext/vector_float2.hpp>

class Sprite {
public:
  Sprite() {}
  Texture *getTexture() { return this->texture; }
  // getTexCoords()
  int getTexId() { return texture == nullptr ? -1 : texture->id; };
  void setTexture(Texture *texture) { this->texture = texture; }
  void setTexCoords(glm::vec2 texCoords[4]) {
    for (int i = 0; i < 4; i++) {
      this->texCoords[i] = texCoords[i];
    }
  }
  float getWidth() { return this->width; }
  void setWidth(float width) { this->width = width; }
  float getHeight() { return this->height; }
  void setHeight(float height) { this->height = height; }

private:
  float width, height;
  Texture *texture = nullptr;
  glm::vec2 texCoords[4] = {glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0),
                            glm::vec2(0, 1)};
};

#endif // SPRITE_HPP
