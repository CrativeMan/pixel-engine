#include <GL/glew.h>

#include "../engine/windowing/Window.hpp"
#include "../system/System.hpp"
#include "../system/logger.hpp"
#include <GLFW/glfw3.h>

#define ID "engine"

int main() {
  Logger::getInstance().setLogFile(LOG_FILE_PATH);
#ifdef DEBUG
  Logger::setLoggerLevel(LogLevel::TRACE);
#else
  Logger::setLoggerLevel(LogLevel::INFO);
#endif

  LOG_INFO("Starting engine");
  Window window;
  window.init(1920, 1080, "engine");
  window.loop();
  window.shutdown();
  LOG_INFO("Shutting down engine");
  return 0;
}
