#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <cwchar>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <string>

#include "../../../system/logger.hpp"
#include "../../assets/AssetPool.hpp"
#include "../ecs/Components.hpp"

#include "Scene.hpp"

#define ID "les"

LevelEditorScene::LevelEditorScene() {}

void LevelEditorScene::init() {
  this->loadResources();
  this->camera = new Camera();
  this->camera->init(glm::vec2(-250, 0));
  this->renderer = new Renderer();

  int xOffset = 10;
  int yOffset = 10;

  float totalWidth = (float)(600 - xOffset * 2);
  float totalHeight = (float)(300 - yOffset * 2);
  float sizeX = totalWidth / 100.0f;
  float sizeY = totalHeight / 100.0f;
  float padding = 3;

  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {
      float xPos = xOffset + (x * sizeX) + (padding * x);
      float yPos = yOffset + (y * sizeY) + (padding * y);
      std::string name = "Obj" + std::to_string(x) + " " + std::to_string(y);
      GameObject *go = new GameObject(
          name, new Transform(glm::vec2(xPos, yPos), glm::vec2(sizeX, sizeY)));
      go->addComponent(new SpriteRenderComponent(
          glm::vec4(xPos / totalWidth, yPos / totalHeight, 1, 1)));
      this->addGameObject(go);
      LOG_TRACE("Added game object %s", name.c_str());
    }
  }

  LOG_TRACE("Gameobject count %d", this->gameObjects.size());
}

void LevelEditorScene::loadResources() {
  this->shader =
      AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");

  // this should be reconsidered
  // std::shared_ptr<Spritesheet> sprs =
  //     std::make_shared<Spritesheet>(this->texture, 16, 16, 100, 0);
  // AssetPool::addSpriteSheet("texture/atlas.png", sprs);
  // this->sps = AssetPool::getSpritesheet("texture/atlas.png");
  // if (this->sps) {
  //   LOG_INFO("Sprite sheet is not null");
  //   this->sprite = this->sps->getSprite(0);
  // } else {
  //   LOG_ERROR("Spritesheet is null");
  // }
  LOG_INFO("Loaded resources for LevelEditorScene");
}

void LevelEditorScene::update(float deltaTime) { (void)deltaTime; }

void LevelEditorScene::render(float dt) {
  std::cout << "Fps" << (1.0f / dt) << std::endl;

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
