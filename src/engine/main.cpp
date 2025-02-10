#include <GL/glew.h>

#include "system/System.hpp"
#include "system/logger.hpp"
#include "windowing/Window.hpp"
#include <GLFW/glfw3.h>

#define ID "engine"

int main(int argc, char **argv) {
  Logger::getInstance().setLogFile(LOG_FILE_PATH);
  Logger::setLoggerLevel(argc, argv);
  Logger::testLogger();

  LOG_INFO("Starting engine");
  Window window;
  window.init(1920, 1080, "engine");
  window.loop();
  window.shutdown();
  LOG_INFO("Shutting down engine");
  return 0;
}
