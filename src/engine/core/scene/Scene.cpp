#include "Scene.hpp"
#include <memory>

void Scene::init() {}

void Scene::start() {
  for (std::unique_ptr<GameObject> &go : this->gameObjects) {
    go->start();
    // this->renderer.addGameObject(go);
  }
  this->isRunning = true;
}

void Scene::addGameObject(GameObject *go) {
  if (!isRunning)
    this->gameObjects.push_back(std::unique_ptr<GameObject>(go));
  else {
    this->gameObjects.push_back(std::unique_ptr<GameObject>(go));
    this->gameObjects.back()->start();
    // this->renderer.addGameObject(this->gameObjects.back());
  }
}

void Scene::update(float deltaTime) {}

void Scene::render() {}
