#include <GL/glew.h>

#include "../header/typedefs.h"
#include "../system/fileHandler.h"
#include "../system/logger.h"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include <cstdio>
#include <stdlib.h>

#define ID "window"

float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

Window::Window() {}

Window::Window(int width, int height, std::string title) {
  this->width = width;
  this->height = height;
  this->title = title.c_str();
  init(width, height, title);
}

void Window::init(int width, int heigh, std::string title) {
  loggerInfo(ID, "Initializing window");
  if (!glfwInit()) {
    loggerError(ID, "Failed to initialize glfw. Aborting");
    assert(false);
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  id = glfwCreateWindow(width, heigh, title.c_str(), NULL, NULL);
  if (id == NULL) {
    loggerError(ID, "Failed to create glfw window");
    assert(false);
  }
  loggerInfo(ID, "Created window '%d'", id);

  glfwMakeContextCurrent(id);

  ASSERT(glewInit() == GLEW_OK, "Failed to initialize glew. Aborting")

  glfwSwapInterval(1);
  glfwShowWindow(id);
  glViewport(0, 0, width, heigh);

  this->ui.init(this->id);
}

void Window::shutdown() {
  glfwDestroyWindow(this->id);
  this->ui.shutdown();
}

void Window::loop() {
  unsigned int vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  const char *vertexSource = readFile("assets/shader/vertex.glsl");
  const char *fragmentSource = readFile("assets/shader/fragment.glsl");

  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexSource, NULL);
  glCompileShader(vertex);

  int success;
  char infoLog[512];
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    loggerError(ID, "Vertex shader compilation failed\n%s\n", infoLog);
  }

  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentSource, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    loggerError(ID, "Fragment shader compilation failed\n%s\n", infoLog);
  }

  unsigned int shader = glCreateProgram();
  glAttachShader(shader, vertex);
  glAttachShader(shader, fragment);
  glLinkProgram(shader);

  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader, 512, NULL, infoLog);
    loggerError(ID, "Shader linking failed");
  }

  while (!glfwWindowShouldClose(this->id)) {
    if (glfwGetWindowAttrib(this->id, GLFW_ICONIFIED) != 0) {
      ImGui_ImplGlfw_Sleep(10);
      continue;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    this->ui.render();

    glfwSwapBuffers(this->id);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteProgram(shader);
}
