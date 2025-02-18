#include "LevelEditorScene.h"
#include <clue.hpp>
#include <jade/windowing/Window.hpp>

#include <memory>

int main() {
  std::unique_ptr<Scene> les(new LevelEditorScene);
  Window *window = Window::get();
  window->init(1920, 1080, "test");
  window->scenemanager->changeScene(std::move(les));
  window->loop();
  window->shutdown();
  delete window;
}
