#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include "RenderBatch.hpp"
#include "jade/core/ecs/ecs.hpp"
#include "jade/core/ecs/Components.hpp"

class Renderer {
public:
	Renderer();

	void add(GameObject *go);
	void render();

private:
  std::vector<RenderBatch *> batches;
  void add(SpriteRenderComponent *spr);
};

#endif //RENDERER_HPP
