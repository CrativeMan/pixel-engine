#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <vector>

#include "Component.hpp"
#include "Transform.hpp"

class GameObject {
public:
  Transform transform;
  void start() {}

private:
  std::string name;
  std::vector<Component> components;
  int zindex = 0;
};

#endif // __GAMEOBJECT_H__