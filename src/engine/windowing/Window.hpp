#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GLFW/glfw3.h>
#include <string>
#include "../userInterface/UserInterface.hpp"
#include "../rendering/Shader.hpp"

class Window {
public:
  GLFWwindow *id;
  Shader shader;
  Window();
  Window(int width, int height, std::string title);
  void init(int width, int height, std::string title);
  void loop();
  void shutdown();

private:
  int width;
  int height;
  const char *title;
  UserInterface ui;
};

#endif // WINDOW_HPP
