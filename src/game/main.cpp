#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <jade/windowing/Window.hpp>

#include <jade/assets/AssetPool.hpp>
#include <jade/core/ecs/Components.hpp>

#include <clue.hpp>
#include <jade/core/scene/Scene.hpp>
#include <memory>

class LevelEditorScene : public Scene {
public:
  LevelEditorScene() {}

  ~LevelEditorScene() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
    this->shader->shutdown();
  }

  void init() override {
    this->loadResources();
    this->camera = new Camera();
    this->camera->init(glm::vec2(-250, 0));
    this->renderer = new Renderer();

    LOG_DEBUG("Gameobject count " << this->gameObjects.size());
  }

  void update(float deltaTime) override { (void)deltaTime; }

  void render(float dt) override {
    for (GameObject *go : this->gameObjects) {
      go->update(dt);
    }

    this->renderer->render();
  }

private:
  unsigned int vao, vbo, ebo;
  Shader *shader;
  GameObject *testObj;

  void loadResources() {
    this->shader =
        AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");
    LOG_INFO("Loaded resources for LevelEditorScene");
  }
};

int main() {
  std::unique_ptr<Scene> les(new LevelEditorScene);
  Window *window = Window::get();
  window->init(1920, 1080, "test");
  window->scenemanager->changeScene(std::move(les));
  window->loop();
  window->shutdown();
  delete window;
}