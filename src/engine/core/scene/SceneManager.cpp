#include "Scene.hpp"

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
  currentScene = std::move(newScene); // unique_ptr needs to be moved
  if (currentScene) {
    currentScene->init();
  }
}

void SceneManager::update() {
  if (currentScene) {
    currentScene->run();
  }
}
