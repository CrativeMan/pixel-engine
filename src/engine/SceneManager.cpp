#include <jade/core/scene/Scene.hpp>

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
  currentScene = std::move(newScene);
  if (currentScene) {
    currentScene->init();
    currentScene->start();
  }
}

void SceneManager::update(float deltaTime) {
  if (currentScene) {
    currentScene->update(deltaTime);
    currentScene->render(deltaTime);
  }
}
