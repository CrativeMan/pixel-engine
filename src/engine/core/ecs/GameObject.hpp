#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

class GameObject {
public:
  GameObject(std::string name, /*Transform transform,*/ int zindex);

private:
  std::string name;
  // Transform transform;
  int zindex;
};

#endif // GAMEOBJECT_HPP
