#include <GL/glew.h>

#include "../system/fileHandler.h"
#include "../system/logger.h"
#include "Shader.hpp"
#include <GLFW/glfw3.h>

#define ID "shader"

Shader::Shader() {}

void Shader::init(const char *vertexPath, const char *fragmentPath) {
  this->vertex = vertexPath;
  this->fragment = fragmentPath;

  const char *vertexSource = readFile(vertexPath);
  const char *fragmentSource = readFile(fragmentPath);

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

  this->id = shader;
  loggerInfo(ID, "Generating shader '%d'", this->id);
}

void Shader::shutdown() {
  glDeleteProgram(this->id);
  loggerInfo(ID, "Deleting shader '%d'", this->id);
}

void Shader::attach() { glUseProgram(this->id); }

void Shader::detach() { glUseProgram(0); }

void Shader::setInt() {
  glUniform1i(glGetUniformLocation());
}
