#include <GL/glew.h>

#include "../header/typedefs.h"
#include "../input/Input.hpp"
#include "../system/logger.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>

#define ID "window"

Window::Window(int width, int height, std::string title) {
  this->width = width;
  this->height = height;
  this->title = title.c_str();
  init(width, height, title);
}

void Window::init(int width, int heigh, std::string title) {
  LOG_INFO("Initializing window");
  // init glfw
  if (!glfwInit()) {
    LOG_ERROR("Failed to initialize glfw. Aborting");
    assert(false);
  }

  // init window
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create window
  this->id = glfwCreateWindow(width, heigh, title.c_str(), NULL, NULL);
  if (this->id == NULL) {
    LOG_ERROR("Failed to create glfw window");
    assert(false);
  }
  LOG_INFO("Created window '%d'", this->id);

  // callbacks
  glfwSetCursorPosCallback(this->id, MouseListener::mousePosCallback);
  glfwSetMouseButtonCallback(this->id, MouseListener::mouseButtonCallback);
  glfwSetScrollCallback(this->id, MouseListener::mouseScrollCallback);
  glfwSetKeyCallback(this->id, KeyListener::keyCallback);

  glfwMakeContextCurrent(this->id);

  // init glew
  ASSERT(glewInit() == GLEW_OK, "Failed to initialize glew. Aborting");

  // depth and blending for transparency
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glfwSwapInterval(1);
  glfwShowWindow(this->id);
  glViewport(0, 0, width, heigh);

  // init ui and scenes
  this->ui.init(this->id);
  this->scenemanager.changeScene(std::make_unique<LevelEditorScene>());
}

void Window::shutdown() {
  LOG_INFO("Shuting down window '%d'", this->id);
  glfwDestroyWindow(this->id);
  this->ui.shutdown();
  glfwTerminate();
}

void Window::loop() {
  float beginTime = glfwGetTime();
  float endTime;
  float dt = -1.0f;

  while (!glfwWindowShouldClose(this->id)) {
    // new ui frame
    if (this->ui.newFrame(this->id) == 1)
      continue;

    // input handling
    if (KeyListener::isKeyPressed(GLFW_KEY_Q))
      glfwSetWindowShouldClose(this->id, GLFW_TRUE);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update and rendering
    this->scenemanager.update(dt);
    this->ui.render();

    // udate buffers and poll events
    glfwSwapBuffers(this->id);
    glfwPollEvents();

    // deltatime
    endTime = glfwGetTime();
    dt = endTime - beginTime;
    beginTime = endTime;
  }
}
