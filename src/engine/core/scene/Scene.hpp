#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include "../../assets/Shader.hpp"

class Scene {
public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual void init() = 0;
  virtual void update() = 0;
  virtual void render() = 0;

private:
};

class LevelEditorScene : public Scene {
public:
  LevelEditorScene();
  ~LevelEditorScene();
  void init() override;
  void update() override;
  void render() override;

private:
unsigned int vao, vbo, ebo;
Shader shader;
};

class SceneManager {
private:
  std::unique_ptr<Scene> currentScene;

public:
  void changeScene(std::unique_ptr<Scene> newScene);
  void update();
  Scene *getCurrentScene() const {
    return currentScene.get();
  }
};

#endif // SCENE_HPP
