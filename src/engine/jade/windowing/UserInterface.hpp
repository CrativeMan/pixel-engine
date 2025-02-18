#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

class UserInterface {
public:
  UserInterface();
  void init(GLFWwindow *w);
  int newFrame(GLFWwindow *id);
  void render();
  void shutdown();

private:
};

#endif // USERINTERFACE_HPP
