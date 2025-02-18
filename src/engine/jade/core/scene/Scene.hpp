#ifndef SCENE_HPP
#define SCENE_HPP

#include <jade/assets/Shader.hpp>
#include <jade/core/ecs/ecs.hpp>
#include <jade/rendering/Camera.hpp>
#include <jade/rendering/Renderer.hpp>

#include <memory>
#include <vector>

class Scene {
protected:
  Camera *camera;
  Renderer *renderer;
  std::vector<GameObject *> gameObjects;

public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual void init() = 0;
  void start();
  Camera *getCamera() { return this->camera; }

  virtual void addGameObject(GameObject *go);
  virtual void update(float deltaTime) = 0;
  virtual void render(float dt) = 0;

private:
  bool isRunning = false;
};

class LevelEditorScene : public Scene {
public:
  LevelEditorScene();
  ~LevelEditorScene();
  void init() override;
  void update(float deltaTime) override;
  void render(float dt) override;

private:
  bool first = false;
  unsigned int vao, vbo, ebo;
  Shader *shader;
  GameObject *testObj;

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
