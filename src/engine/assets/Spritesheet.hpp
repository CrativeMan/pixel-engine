#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "Sprite.hpp"
#include "Texture.hpp"
#include <vector>
class Spritesheet {
public:
  Spritesheet(Texture *texture, int spriteWidth, int spriteHeight,
              int numSprites, int spacing);
  Sprite *getSprite(int index);
  size_t size();

private:
  Texture *texture;
  std::vector<Sprite *> sprites;
};

#endif // SPRITESHEET_HPP
