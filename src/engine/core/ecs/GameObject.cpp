#include "ecs.hpp"

GameObject::GameObject(std::string name) { this->name = name; }
void GameObject::start() {
  for (Component *comp : components) {
    comp->start();
  }
}
void GameObject::update(float dt) {
  for (Component *comp : components) {
    comp->update(dt);
  }
}
