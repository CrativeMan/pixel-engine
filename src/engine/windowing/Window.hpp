#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GLFW/glfw3.h>
#include <string>
#include "../userInterface/UserInterface.hpp"

class Window {
public:
  GLFWwindow *id;
  Window();
  Window(int width, int height, std::string title);
  void init(int width, int height, std::string title);
  void shutdown();
  void loop(UserInterface ui);

private:
  int width;
  int height;
  const char *title;
};

#endif // WINDOW_HPP
