#include <GL/glew.h>

#include "../header/typedefs.h"
#include "../system/logger.h"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include <cstdio>
#include <memory>
#include <stdlib.h>

#define ID "window"

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
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->id = glfwCreateWindow(width, heigh, title.c_str(), NULL, NULL);
  if (this->id == NULL) {
    loggerError(ID, "Failed to create glfw window");
    assert(false);
  }
  loggerInfo(ID, "Created window '%d'", this->id);

  glfwMakeContextCurrent(this->id);

  ASSERT(glewInit() == GLEW_OK, "Failed to initialize glew. Aborting");

  glfwSwapInterval(1);
  glfwShowWindow(this->id);
  glViewport(0, 0, width, heigh);

  this->ui.init(this->id);
  this->scenemanager.changeScene(std::make_unique<LevelEditorScene>());
}

void Window::shutdown() {
  loggerInfo(ID, "Shuting down window '%d'", this->id);
  glfwDestroyWindow(this->id);
  this->ui.shutdown();
  glfwTerminate();
}

void Window::loop() {
  while (!glfwWindowShouldClose(this->id)) {
    if (glfwGetWindowAttrib(this->id, GLFW_ICONIFIED) != 0) {
      ImGui_ImplGlfw_Sleep(10);
      continue;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->scenemanager.update();
    this->ui.render();

    glfwSwapBuffers(this->id);
    glfwPollEvents();
  }
}
