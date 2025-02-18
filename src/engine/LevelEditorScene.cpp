#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <cwchar>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <string>

#include <jade/assets/AssetPool.hpp>
#include <jade/core/ecs/Components.hpp>

#include <clue.hpp>
#include <jade/core/scene/Scene.hpp>

#define ID "les"

LevelEditorScene::LevelEditorScene() {}

void LevelEditorScene::init() {
  this->loadResources();
  this->camera = new Camera();
  this->camera->init(glm::vec2(-250, 0));
  this->renderer = new Renderer();

  LOG_DEBUG("Gameobject count " << this->gameObjects.size());
}

void LevelEditorScene::loadResources() {
  this->shader =
      AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");
  LOG_INFO("Loaded resources for LevelEditorScene");
}

void LevelEditorScene::update(float deltaTime) { (void)deltaTime; }

void LevelEditorScene::render(float dt) {
  for (GameObject *go : this->gameObjects) {
    go->update(dt);
  }

  this->renderer->render();
}

LevelEditorScene::~LevelEditorScene() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  glDeleteBuffers(1, &this->ebo);
  this->shader->shutdown();
}
