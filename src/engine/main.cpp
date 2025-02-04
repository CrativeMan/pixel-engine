#include <GL/glew.h>

#include "windowing/Window.hpp"
#include <GLFW/glfw3.h>

#define ID "engine"

int main() {
  Window window;
  window.init(1920, 1080, "engine");
  window.loop();
  window.shutdown();
  return 0;
}
