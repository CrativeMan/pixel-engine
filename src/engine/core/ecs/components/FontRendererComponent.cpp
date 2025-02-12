#include "../Components.hpp"

#include <iostream>

void FontRendererComponenet::start() {
  if (this->parent->getComponent<SpriteRenderComponent>() != nullptr) {
    std::cout << "FontRendererComponent: Found SpriteRenderComponent\n";
  }
}

void FontRendererComponenet::update(float dt) { (void)dt; }