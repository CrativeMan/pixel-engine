#include <GL/glew.h>

#include "../../assets/AssetPool.hpp"
#include "../../system/logger.h"

#include "Scene.hpp"

#define ID "les"

float vertices[] = {
    // positions            // colors         // texture coords
    200.0f, 200.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    200.0f, -0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.0f,  -0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.0f,  200.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

LevelEditorScene::LevelEditorScene() {}

void LevelEditorScene::init() {
  this->loadResources();
  this->shader = AssetPool::getShader("assets/shader/vertex.glsl",
                                      "assets/shader/fragment.glsl");
  this->texture = AssetPool::getTexture("assets/textures/atlas.png");
  this->camera.init(glm::vec2());
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  this->vao = vao;
  this->vbo = vbo;
  this->ebo = ebo;
}

void LevelEditorScene::loadResources() {
  AssetPool::getShader("assets/shader/vertex.glsl",
                       "assets/shader/fragment.glsl");
  AssetPool::getTexture("assets/textures/atlas.png");
  loggerInfo(ID, "Loaded resources for LevelEditorScene");
}

void LevelEditorScene::update(float deltaTime) {
  camera.position.x -= deltaTime * 10.0f;
  camera.position.y -= deltaTime * 10.0f;
}

void LevelEditorScene::render() {
  this->shader->attach();
  this->shader->setMat4("uProjectionMatrix",
                        this->camera.getProjectionMatrix());
  this->shader->setMat4("uViewMatrix", this->camera.getViewMatrix());
  glBindTexture(GL_TEXTURE_2D, this->texture->id);
  glBindVertexArray(this->vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  this->shader->detach();
}

LevelEditorScene::~LevelEditorScene() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  glDeleteBuffers(1, &this->ebo);
  this->shader->shutdown();
}
