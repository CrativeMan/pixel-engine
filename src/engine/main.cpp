#include <GL/glew.h>

#include "windowing/Window.hpp"
#include "system/logger.h"
#include <GLFW/glfw3.h>

#define ID "engine"

int main() {
  loggerInfo(ID, "Initializing engine");
  Window window;
  std::string title = "engine";
  window.init(1920, 1080, title);
  window.loop();

  loggerInfo(ID, "Shuting down engine");
  window.shutdown();
  glfwTerminate();
  return 0;
}
