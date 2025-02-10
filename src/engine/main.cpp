#include <GL/glew.h>

#include "system/logger.h"
#include "windowing/Window.hpp"
#include <GLFW/glfw3.h>

#define ID "engine"

int main() {
  loggerInfo("engine", "Starting engine");
  Window window;
  window.init(1920, 1080, "engine");
  window.loop();
  window.shutdown();
  loggerInfo("engine", "Stopping engine");
  return 0;
}
