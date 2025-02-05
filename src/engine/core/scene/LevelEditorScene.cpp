#include "Scene.hpp"

#include <GL/glew.h>

float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

LevelEditorScene::LevelEditorScene() {}

void LevelEditorScene::init() {
  this->shader.init("assets/shader/vertex.glsl", "assets/shader/fragment.glsl");
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
  this->vao = vao;
  this->vbo = vbo;
}

void LevelEditorScene::update() {}

void LevelEditorScene::render() {
  this->shader.bind();
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

LevelEditorScene::~LevelEditorScene() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  this->shader.shutdown();
}
