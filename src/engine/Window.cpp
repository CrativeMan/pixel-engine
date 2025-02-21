#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <clue.hpp>
#include <jade/header/typedefs.h>
#include <jade/windowing/Input.hpp>
#include <jade/windowing/Window.hpp>

Window *Window::window = nullptr;
SceneManager *Window::scenemanager = nullptr;

Window *Window::get() {
  if (Window::window == nullptr) {
    Window::window = new Window();
  }
  return Window::window;
}

void Window::init(int width, int heigh, std::string title) {
  LOG_INFO("Initializing window");
  // init glfw
  if (!glfwInit()) {
    LOG_ERROR("Failed to initialize glfw. Aborting");
    assert(false);
  }
  LOG_DEBUG("Initialized glfw");

  // init window
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  LOG_DEBUG("Set window hints");

  // create window
  this->id = glfwCreateWindow(width, heigh, title.c_str(), NULL, NULL);
  if (this->id == NULL) {
    LOG_ERROR("Failed to create glfw window");
    assert(false);
  }
  LOG_DEBUG("Created window '" << this->id << "'");

  // callbacks
  glfwSetCursorPosCallback(this->id, MouseListener::mousePosCallback);
  glfwSetMouseButtonCallback(this->id, MouseListener::mouseButtonCallback);
  glfwSetScrollCallback(this->id, MouseListener::mouseScrollCallback);
  glfwSetKeyCallback(this->id, KeyListener::keyCallback);
  LOG_DEBUG("Set callbacks");

  glfwMakeContextCurrent(this->id);

  // init glew
  ASSERT(glewInit() == GLEW_OK, "Failed to initialize glew. Aborting");
  LOG_DEBUG("Initialized glew");

  // depth and blending for transparency
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  LOG_DEBUG("Enabled depth test and blending");

  glfwSwapInterval(1);
  glfwShowWindow(this->id);
  glViewport(0, 0, width, heigh);
  LOG_DEBUG("Set viewport");

  // init ui and scenes
  this->ui.init(this->id);
}

void Window::shutdown() {
  LOG_INFO("Shuting down window '" << this->id << "'");
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
    this->scenemanager->update(dt);
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
