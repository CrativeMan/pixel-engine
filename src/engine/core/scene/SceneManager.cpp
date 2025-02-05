#include "Scene.hpp"

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
  currentScene = std::move(newScene);
  if (currentScene) {
    currentScene->init();
  }
}

void SceneManager::update() {
  if (currentScene) {
    currentScene->update();
    currentScene->render();
  }
}
