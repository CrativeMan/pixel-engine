#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "../core/scene/Scene.hpp"
#include "../userInterface/UserInterface.hpp"
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
GLFWwindow *id;
  static Window *window;
  static SceneManager *scenemanager;

  static Window *get();
  void init(int width, int height, std::string title);
  void loop();
  void shutdown();

private:
  int width;
  int height;
  const char *title;
  UserInterface ui;

  Window(){this->window = nullptr; this->scenemanager = new SceneManager();};
  void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
  }
};

#endif // WINDOW_HPP
