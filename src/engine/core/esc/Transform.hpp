#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <glm/ext/vector_float2.hpp>
class Transform {
public:
  glm::vec2 position;
  glm::vec2 scale;

  Transform() : position(0.0f), scale(1.0f) {}
  Transform(glm::vec2 position, glm::vec2 scale)
      : position(position), scale(scale) {}

  void init(glm::vec2 position, glm::vec2 scale) {
    this->position = position;
    this->scale = scale;
  }

  void copy(Transform to) {
    this->position = to.position;
    this->scale = to.scale;
  }

  Transform *copy() { return new Transform(this->position, this->scale); }

  /*
    Override the equals operator to compare two Transforms
  */
  bool operator==(Transform &other) {
    if (this == &other)
      return true;
    return this->position == other.position && this->scale == other.scale;
  }
};

#endif // __TRANSFORM_H__