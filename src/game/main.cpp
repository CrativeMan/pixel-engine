#include <jade/windowing/Window.hpp>

int main() {
  Window *window = Window::get();
  window->init(1920, 1080, "test");
  window->loop();
  window->shutdown();
  delete window;
}