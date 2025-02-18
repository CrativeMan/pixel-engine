#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include <jade/assets/AssetPool.hpp>
#include <jade/rendering/RenderBatch.hpp>
#include <jade/windowing/Window.hpp>

RenderBatch::RenderBatch(int maxBatchSize) {
  this->shader =
      AssetPool::getShader("shader/vertex.glsl", "shader/fragment.glsl");
  this->maxBatchSize = maxBatchSize;

  this->vertices = new float[maxBatchSize * 4 * VERTEX_SIZE];

  this->numSprites = 0;
  this->room = true;
}

void RenderBatch::start() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  unsigned int ebo;
  glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &ebo);
  int *indices = generateIndices();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES,
                        (void *)POS_OFFSET);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES,
                        (void *)COLOR_OFFSET);
  glEnableVertexAttribArray(1);
}

void RenderBatch::addSprite(SpriteRenderComponent *spr) {
  int index = this->numSprites;
  this->sprites[index] = spr;
  this->numSprites++;

  loadVertexProperties(index);

  if (numSprites >= this->maxBatchSize)
    this->room = false;
}

void RenderBatch::render() {
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

  this->shader->attach();
  this->shader->setMat4("uProjectionMatrix",
                        Window::get()
                            ->scenemanager->getCurrentScene()
                            ->getCamera()
                            ->getProjectionMatrix());
  this->shader->setMat4("uViewMatrix", Window::get()
                                           ->scenemanager->getCurrentScene()
                                           ->getCamera()
                                           ->getViewMatrix());
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians((float)glfwGetTime()),
                      glm::vec3(0, 0, 1));
  this->shader->setMat4("uModelMatrix", model);

  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawElements(GL_TRIANGLES, this->numSprites * 6, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);

  this->shader->detach();
}

void RenderBatch::loadVertexProperties(int index) {
  SpriteRenderComponent *spr = this->sprites[index];
  int offset = index * 4 * VERTEX_SIZE;
  glm::vec4 Color = spr->getColor();

  float xAdd = 1.0f;
  float yAdd = 1.0f;
  for (int i = 0; i < 4; i++) {
    if (i == 1)
      yAdd = 0.0f;
    else if (i == 2)
      xAdd = 0.0f;
    else if (i == 3)
      yAdd = 1.0f;

    vertices[offset] = spr->parent->transform->position.x +
                       (xAdd * spr->parent->transform->scale.x);
    vertices[offset + 1] = spr->parent->transform->position.y +
                           (yAdd * spr->parent->transform->scale.y);

    vertices[offset + 2] = Color.x;
    vertices[offset + 3] = Color.y;
    vertices[offset + 4] = Color.z;
    vertices[offset + 5] = Color.w;

    offset += VERTEX_SIZE;
  }
}

int *RenderBatch::generateIndices() {
  int *elements = new int[6 * this->maxBatchSize];
  for (int i = 0; i < maxBatchSize; i++) {
    int offsetArrayIndex = 6 * i;
    int offset = 4 * i;

    elements[offsetArrayIndex] = offset + 3;
    elements[offsetArrayIndex + 1] = offset + 2;
    elements[offsetArrayIndex + 2] = offset + 0;

    elements[offsetArrayIndex + 3] = offset + 0;
    elements[offsetArrayIndex + 4] = offset + 2;
    elements[offsetArrayIndex + 5] = offset + 1;
  }
  return elements;
}

bool RenderBatch::hasRoom() { return this->room; }
