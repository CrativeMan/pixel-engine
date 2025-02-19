#include <clue.hpp>
#include <jade/core/scene/Scene.hpp>

void Scene::init() {}

void Scene::start() {
  this->isRunning = true;
  LOG_DEBUG("Started scene");
}

void Scene::update(float deltaTime) { (void)deltaTime; }

void Scene::render(float dt) { (void)dt; }
