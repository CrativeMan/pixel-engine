#include "LevelEditorScene.h"
#include <array>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <jade/assets/AssetPool.hpp>

std::array<float, 9> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  0.0f,  0.5f, 0.0f};

LevelEditorScene::LevelEditorScene() {}

LevelEditorScene::~LevelEditorScene() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  glDeleteBuffers(1, &this->ebo);
  this->shader->shutdown();
}

void LevelEditorScene::init() {
  this->loadResources();
  this->camera = new Camera();
  this->camera->init(glm::vec2(-100));

  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);
  glGenBuffers(1, &this->vbo);

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

void LevelEditorScene::loadResources() {
  this->shader =
      AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");
  LOG_INFO("Loaded resources for LevelEditorScene");
}

void LevelEditorScene::update(float dt) {}

void LevelEditorScene::render(float dt) {
  this->shader->attach();
  this->shader->setMat4("uProjectionMatrix",
                        this->camera->getProjectionMatrix());
  this->shader->setMat4("uViewMatrix", this->camera->getViewMatrix());
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(100));
  this->shader->setMat4("uModelMatrix", model);
  glBindVertexArray(this->vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
