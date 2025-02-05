#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "../core/scene/Scene.hpp"
#include "../userInterface/UserInterface.hpp"
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
  GLFWwindow *id;
  SceneManager scenemanager;

  Window() {};
  Window(int width, int height, std::string title);
  void init(int width, int height, std::string title);
  void loop();
  void shutdown();

private:
  int width;
  int height;
  const char *title;
  UserInterface ui;

  void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
  }
};

#endif // WINDOW_HPP
