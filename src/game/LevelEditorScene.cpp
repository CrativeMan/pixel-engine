#include "LevelEditorScene.h"
#include <jade/assets/AssetPool.hpp>

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
  this->camera->init(glm::vec2(-250, 0));
}

void LevelEditorScene::loadResources() {
  this->shader =
      AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");
  LOG_INFO("Loaded resources for LevelEditorScene");
}

void LevelEditorScene::update(float dt) {}

void LevelEditorScene::render(float dt) {}
