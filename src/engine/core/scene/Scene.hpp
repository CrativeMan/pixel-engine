#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

class Scene {
public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual void init() = 0;
  virtual void run() = 0;

private:
};

class LevelEditorScene : public Scene {
public:
  LevelEditorScene();
  void init() override;
  void run() override;
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
