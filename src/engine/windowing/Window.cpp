#include <GL/glew.h>

#include "../header/logger.h"
#include "../header/typedefs.h"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include <cstdio>
#include <stdlib.h>

#define ID "window"

Window::Window() {
}

Window::Window(int width, int height, std::string title) {
  this->width = width;
  this->height = height;
  this->title = title.c_str();
  init(width, height, title);
}

void Window::init(int width, int heigh, std::string title) {
  loggerInfo(ID, "Initializing window");
  if (!glfwInit()) {
    loggerError(ID, "Failed to initialize glfw. Aborting");
    assert(false);
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  id = glfwCreateWindow(width, heigh, title.c_str(), NULL, NULL);
  if (id == NULL) {
    loggerError(ID, "Failed to create glfw window");
    assert(false);
  }
  loggerInfo(ID, "Created window '%d'", id);

  glfwMakeContextCurrent(id);

  ASSERT(glewInit() == GLEW_OK, "Failed to initialize glew. Aborting")

  glfwSwapInterval(1);
  glfwShowWindow(id);
  glViewport(0, 0, width, heigh);
}
