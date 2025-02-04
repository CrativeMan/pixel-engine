#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
  GLFWwindow *id;
  Window();
  Window(int width, int height, std::string title);
  void init(int width, int height, std::string title);

private:
  int width;
  int height;
  const char *title;
};

#endif // WINDOW_HPP
