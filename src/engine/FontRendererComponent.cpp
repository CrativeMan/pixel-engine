#include <iostream>
#include <jade/core/ecs/Components.hpp>

void FontRendererComponenet::start() {
  if (this->parent->getComponent<SpriteRenderComponent>() != nullptr) {
    std::cout << "FontRendererComponent: Found SpriteRenderComponent\n";
  }
}

void FontRendererComponenet::update(float dt) { (void)dt; }