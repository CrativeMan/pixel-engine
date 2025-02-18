#include <jade/core/ecs/Transform.hpp>
#include <jade/core/ecs/ecs.hpp>

GameObject::GameObject(std::string name) { this->name = name; }
GameObject::GameObject(std::string name, Transform *transform) {
  this->name = name;
  this->transform = transform;
}
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
