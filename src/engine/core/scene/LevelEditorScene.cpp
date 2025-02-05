#include "Scene.hpp"

#include <GL/glew.h>

/*
 *(-0.5, 0.5)   *(0,5, 0,5)
 *(-0.5, -0.5)   *(0,5, -0,5)
 */

float vertices[] = {
    -0.5f, -0.5f, 0.0f, // 0
    0.5f,  0.5f,  0.0f, // 1
    -0.5f, 0.5f,  0.0f, // 2
    0.5f,  -0.5f, 0.0f, // 3
};

unsigned int indices[] = {0, 1, 2, 0, 3, 1};

LevelEditorScene::LevelEditorScene() {}

void LevelEditorScene::init() {
  this->shader.init("assets/shader/vertex.glsl", "assets/shader/fragment.glsl");
  unsigned int vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  this->vao = vao;
  this->vbo = vbo;
  this->ebo = ebo;
}

void LevelEditorScene::update() {}

void LevelEditorScene::render() {
  this->shader.bind();
  glBindVertexArray(vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

LevelEditorScene::~LevelEditorScene() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  this->shader.shutdown();
}
