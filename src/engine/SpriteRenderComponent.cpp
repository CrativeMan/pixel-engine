#include <glm/ext/vector_float4.hpp>
#include <iostream>
#include <jade/core/ecs/Components.hpp>

SpriteRenderComponent::SpriteRenderComponent(glm::vec4 color) {
  this->color = color;
}

void SpriteRenderComponent::start() { std::cout << "src am starting\n"; }

void SpriteRenderComponent::update(float dt) {
  (void)dt;
  if (!first) {
    std::cout << "src am updating\n";
    first = true;
  }
}
