#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
public:
  glm::vec2 position;
  Camera();
  Camera(glm::vec2 position);
  void init(glm::vec2 position);
  void adjustProjection();
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();
  glm::mat4 getInverseViewMatrix();
  glm::mat4 getInverseProjectionMatrix();
  glm::vec2 getProjectionSize();

private:
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 inverseProjectionMatrix;
  glm::mat4 inverseViewMatrix;
  glm::vec2 projectionSize = glm::vec2(32.0f * 40.0f, 32.0f * 21.0f);
};

#endif // CAMERA_HPP
