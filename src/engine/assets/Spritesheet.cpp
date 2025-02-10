#include "Spritesheet.hpp"
#include "Sprite.hpp"

Spritesheet::Spritesheet(Texture *texture, int spriteWidth, int spriteHeight,
                         int numSprites, int spacing) {
  this->texture = texture;
  for (int i = 0; i < numSprites; i++) {
    
  }
}

Sprite Spritesheet::getSprite(int index) { return Sprite(); }
int Spritesheet::size() { return -1; }
