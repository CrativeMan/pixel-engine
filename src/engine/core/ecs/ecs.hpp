#ifndef ESC_HPP
#define ESC_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "Transform.hpp"

class GameObject;

class Component {
public:
  GameObject *parent = nullptr;
  virtual void start() = 0;
  virtual void update(float dt) = 0;
  virtual void imgui() = 0;
};

class GameObject {
public:
  GameObject(std::string name);
  GameObject(std::string name, Transform *transform);
  Transform *transform;

  void start();
  void update(float dt);

  template <typename T> void addComponent(T *comp) {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must inherit from Component");
    this->components.push_back(comp);
    comp->parent = this;
  }

  template <typename T> T *getComponent() {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must inherit from Component");
    for (Component *comp : components) {
      if (T *cast = dynamic_cast<T *>(comp)) {
        return cast;
      }
    }
    return nullptr;
  }

  template <typename T> void removeComponent() {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must inherit from Component");
    auto it = std::remove_if(
        components.begin(), components.end(),
        [](Component *comp) { return dynamic_cast<T *>(comp) != nullptr; });

    for (auto i = it; i != components.end(); ++i) {
      delete *i;
    }
    components.erase(it, components.end());
  }

private:
  std::string name;
  std::vector<Component *> components;
  int zindex = 0;
};

#endif // ESC_HPP
