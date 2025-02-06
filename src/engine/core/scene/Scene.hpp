#ifndef SCENE_HPP
#define SCENE_HPP

#include "../../assets/Shader.hpp"
#include "../../assets/Texture.hpp"
#include "../../rendering/Camera.hpp"
#include "../../rendering/Renderer.hpp"

#include <memory>

class Scene {
protected:
  Renderer renderer;
  Camera camera;
  bool isRunning = false;
  bool levelLoaded = false;

public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual void init() = 0;
  virtual void start() {}
  virtual void addGameObject() {}
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
  Texture *texture;

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
