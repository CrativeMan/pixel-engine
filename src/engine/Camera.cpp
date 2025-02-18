#include <jade/rendering/Camera.hpp>
#include <clue.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera() {}

Camera::Camera(glm::vec2 position) { init(position); }

void Camera::init(glm::vec2 position) {
  this->position = position;
  this->projectionMatrix = glm::mat4(1.0f);
  this->viewMatrix = glm::mat4(1.0f);
  this->inverseProjectionMatrix = glm::mat4(1.0f);
  this->inverseViewMatrix = glm::mat4(1.0f);
  adjustProjection();
  LOG_INFO("Camera initiaed at position: " << this->position.x << " "
                                           << this->position.y);
}

void Camera::adjustProjection() {
  this->projectionMatrix = glm::mat4(1.0f);
  this->projectionMatrix =
      glm::ortho(0.0f, projectionSize.x, 0.0f, projectionSize.y, 0.0f, 100.0f);
  this->inverseProjectionMatrix = glm::inverse(this->projectionMatrix);
}

glm::mat4 Camera::getViewMatrix() {
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  this->viewMatrix = glm::mat4(1.0f);
  this->viewMatrix = glm::lookAt(
      glm::vec3(position.x, position.y, 20.0f),
      cameraFront + glm::vec3(position.x, position.y, 0.0f), cameraUp);
  this->inverseViewMatrix = glm::inverse(this->viewMatrix);
  return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() { return this->projectionMatrix; }
glm::mat4 Camera::getInverseViewMatrix() { return this->inverseViewMatrix; }
glm::mat4 Camera::getInverseProjectionMatrix() {
  return this->inverseProjectionMatrix;
}
glm::vec2 Camera::getProjectionSize() { return this->projectionSize; }
