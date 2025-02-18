#include <clue.hpp>
#include <jade/core/ecs/ecs.hpp>
#include <jade/core/scene/Scene.hpp>

void Scene::init() {}

void Scene::start() {
  for (GameObject *go : gameObjects) {
    go->start();
    this->renderer->add(go);
  }
  this->isRunning = true;
  LOG_DEBUG("Started scene");
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
