#include <GL/glew.h>

#include "userInterface/UserInterface.hpp"
#include "windowing/Window.hpp"
#include "header/logger.h"
#include <GLFW/glfw3.h>

#define ID "engine"

int main() {
  loggerInfo(ID, "Initializing engine");
  Window window;
  UserInterface ui;
  std::string title = "engine";
  window.init(1920, 1080, title);
  ui.init(window.id);

  loggerInfo(ID, "Starting window loop");
  while (!glfwWindowShouldClose(window.id)) {
    if (glfwGetWindowAttrib(window.id, GLFW_ICONIFIED) != 0) {
      ImGui_ImplGlfw_Sleep(10);
      continue;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ui.render();

    glfwSwapBuffers(window.id);
    glfwPollEvents();
  }

  loggerInfo(ID, "Shuting down engine");
  glfwDestroyWindow(window.id);
  ui.shutdown();
  glfwTerminate();
  return 0;
}
