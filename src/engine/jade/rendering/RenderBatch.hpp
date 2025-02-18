#ifndef RENDERBATCH_HPP
#define RENDERBATCH_HPP

#include <jade/assets/Shader.hpp>
#include <jade/core/ecs/Components.hpp>
#include <vector>

#define POS_SIZE 2
#define COLOR_SIZE 4

#define POS_OFFSET 0
#define COLOR_OFFSET (POS_OFFSET + POS_SIZE * sizeof(float))
#define VERTEX_SIZE 6
#define VERTEX_SIZE_BYTES (VERTEX_SIZE * sizeof(float))

class RenderBatch {
public:
  RenderBatch(int maxBatchSize);
  void start();
  void addSprite(SpriteRenderComponent *spr);
  void render();
  bool hasRoom();

private:
  // important to check if numSprites is reached
  std::vector<SpriteRenderComponent *> sprites;
  int numSprites;
  bool room;
  float *vertices;

  unsigned int vao, vbo;
  int maxBatchSize;
  Shader *shader;

  void loadVertexProperties(int index);
  int *generateIndices();
};

#endif // RENDERBATCH_HPP
