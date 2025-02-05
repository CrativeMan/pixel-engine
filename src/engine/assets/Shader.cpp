#include <GL/glew.h>

#include "../system/fileHandler.h"
#include "../system/logger.h"
#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>

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

void Shader::setInt(std::string name, int value) {
  glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setFloat(std::string name, float value) {
  glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setVec3(std::string name, glm::vec3 value) {
  glUniform3f(glGetUniformLocation(this->id, name.c_str()), value.x, value.y,
              value.z);
}

void Shader::setVec4(std::string name, glm::vec4 value) {
  glUniform4f(glGetUniformLocation(this->id, name.c_str()), value.x, value.y,
              value.z, value.w);
}

void Shader::setMat4(std::string name, glm::mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(value));
}
