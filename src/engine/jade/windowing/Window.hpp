#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GLFW/glfw3.h>
#include <jade/core/scene/Scene.hpp>
#include <jade/windowing/UserInterface.hpp>
#include <string>

/*
@brief Jade's class for handling windowing tasks and the main loop
@details This class is a singleton and is responsible for creating the window,
handling the main loop and shutting down the window
@param id The GLFWwindow id
@param window The singleton instance of the window
@param scenemanager The SceneManager instance
@param width The width of the window
@param height The height of the window
@param title The title of the window
@param ui The UserInterface instance
*/
class Window {
public:
  GLFWwindow *id;
  static Window *window;
  static SceneManager *scenemanager;

  /*
  @brief Get the singleton instance of the window
  @return The singleton instance of the window
  */
  static Window *get();
  /*
  @brief Initialize the window
  @param width The width of the window
  @param height The height of the window
  @param title The title of the window
  */
  void init(int width, int height, std::string title);
  void loop();
  void shutdown();

private:
  int width;
  int height;
  const char *title;
  UserInterface ui;

  Window() {
    this->window = nullptr;
    this->scenemanager = new SceneManager();
  };
  void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
  }
};

#endif // WINDOW_HPP
