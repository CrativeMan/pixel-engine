#include "../Components.hpp"
#include <iostream>

void SpriteRenderComponent::start() { std::cout << "src am starting\n"; }

void SpriteRenderComponent::update(float dt) {
  (void)dt;
  if (!first) {
    std::cout << "src am updating\n";
    first = true;
  }
}