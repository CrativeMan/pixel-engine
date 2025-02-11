#ifndef SCENE_HPP
#define SCENE_HPP

#include "../../assets/Shader.hpp"
#include "../../rendering/Camera.hpp"
#include "../../rendering/Renderer.hpp"
#include "../esc/GameObject.hpp"

#include <memory>
#include <vector>

class Scene {
protected:
  Renderer renderer;
  Camera camera;
  std::vector<std::unique_ptr<GameObject>> gameObjects;
  GameObject *activeGameObject = nullptr;
  bool isRunning = false;
  bool levelLoaded = false;

public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual void init() = 0;
  void start();
  virtual void addGameObject(GameObject *go);
  virtual void update(float deltaTime) = 0;
  virtual void render() = 0;

private:
};

class LevelEditorScene : public Scene {
public:
  LevelEditorScene();
  ~LevelEditorScene();
  void init() override;
  void update(float deltaTime) override;
  void render() override;

private:
  unsigned int vao, vbo, ebo;
  Shader *shader;

  void loadResources();
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
