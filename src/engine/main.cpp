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
  window.loop(ui);

  loggerInfo(ID, "Shuting down engine");
  ui.shutdown();
  glfwTerminate();
  return 0;
}
