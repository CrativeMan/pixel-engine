#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <cwchar>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

#include "../../assets/AssetPool.hpp"
#include "../../system/logger.hpp"

#include "Scene.hpp"

#define ID "les"

float vertices[] = {
    // positions          // colors         // texture coords
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
  this->camera.init(glm::vec2(-300, -300));

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
  this->shader =
      AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");

  // this should be reconsidered
  // std::shared_ptr<Spritesheet> sprs =
  //     std::make_shared<Spritesheet>(this->texture, 16, 16, 100, 0);
  // AssetPool::addSpriteSheet("texture/atlas.png", sprs);
  // this->sps = AssetPool::getSpritesheet("texture/atlas.png");
  // if (this->sps) {
  //   LOG_INFO("Sprite sheet is not null");
  //   this->sprite = this->sps->getSprite(0);
  // } else {
  //   LOG_ERROR("Spritesheet is null");
  // }
  LOG_INFO("Loaded resources for LevelEditorScene");
}

void LevelEditorScene::update(float deltaTime) {}

void LevelEditorScene::render() {
  this->shader->attach();
  glBindVertexArray(this->vao);
  //  glBindTexture(GL_TEXTURE_2D, this->sprite->getTexId());

  this->shader->setMat4("uProjectionMatrix",
                        this->camera.getProjectionMatrix());
  this->shader->setMat4("uViewMatrix", this->camera.getViewMatrix());

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians((float)glfwGetTime()),
                      glm::vec3(0, 0, 1));
  this->shader->setMat4("uModelMatrix", model);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  this->shader->detach();
}

LevelEditorScene::~LevelEditorScene() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
  glDeleteBuffers(1, &this->ebo);
  this->shader->shutdown();
}
