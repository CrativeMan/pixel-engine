#include "Scene.hpp"
#include "../../../system/logger.hpp"
#include "../ecs/ecs.hpp"

void Scene::init() {}

void Scene::start() {
  for (GameObject *go : gameObjects) {
    go->start();
    this->renderer->add(go);
  }
  this->isRunning = true;
  LOG_TRACE("Started scene");
}

void Scene::addGameObject(GameObject *go) {
  if (!isRunning) {
    gameObjects.push_back(go);
  } else {
    gameObjects.push_back(go);
    go->start();
    this->renderer->add(go);
  }
}

void Scene::update(float deltaTime) { (void)deltaTime; }

void Scene::render(float dt) { (void)dt; }
