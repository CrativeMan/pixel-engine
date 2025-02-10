#include "Spritesheet.hpp"
#include "Sprite.hpp"
#include <cstddef>
#include <cstdlib>

Spritesheet::Spritesheet(Texture *texture, int spriteWidth, int spriteHeight,
                         int numSprites, int spacing) {
  this->texture = texture;
  float textureHeight = (float)texture->getHeight();
  float textureWidth = (float)texture->getWidth();
  int currentX = 0;
  int currentY = texture->getHeight() - spriteHeight;
  for (int i = 0; i < numSprites; i++) {
    float topY = (currentY + spriteHeight) / textureHeight;
    float rightX = (currentX + spriteWidth) / textureWidth;
    float leftX = currentX / textureWidth;
    float bottomY = currentY / textureHeight;

    glm::vec2 texCoords[4] = {
        glm::vec2(rightX, topY),
        glm::vec2(rightX, bottomY),
        glm::vec2(leftX, bottomY),
        glm::vec2(leftX, topY),
    };

    Sprite *sprite = new Sprite();
    sprite->setTexture(this->texture);
    sprite->setTexCoords(texCoords);
    sprite->setWidth(spriteWidth);
    sprite->setHeight(spriteHeight);
    this->sprites.push_back(sprite);

    currentX += spriteWidth + spacing;
    if (currentX >= texture->getWidth()) {
      currentX = 0;
      currentY -= spriteHeight + spacing;
    }
  }
}

Sprite *Spritesheet::getSprite(int index) {
  if (index < 0 || index >= sprites.size())
    return nullptr;

  return this->sprites[index];
}
size_t Spritesheet::size() { return this->sprites.size(); }
