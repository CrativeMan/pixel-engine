#ifndef SCENE_HPP
#define SCENE_HPP

#include <jade/assets/Shader.hpp>
#include <jade/rendering/Camera.hpp>

#include <memory>

class Scene {
protected:
  Camera *camera;

public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual void init() = 0;
  void start();
  Camera *getCamera() { return this->camera; }

  virtual void update(float deltaTime) = 0;
  virtual void render(float dt) = 0;

private:
  bool isRunning = false;
};

class SceneManager {
private:
  std::unique_ptr<Scene> currentScene;

public:
  void changeScene(std::unique_ptr<Scene> newScene);
  void update(float deltaTime);
  Scene *getCurrentScene() const { return currentScene.get(); }
};

#endif // SCENE_HPP
