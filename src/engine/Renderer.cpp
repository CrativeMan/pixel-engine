#include <jade/rendering/RenderBatch.hpp>
#include <jade/rendering/Renderer.hpp>

Renderer::Renderer() {}

void Renderer::add(GameObject *go) {
  SpriteRenderComponent *spr = go->getComponent<SpriteRenderComponent>();
  if (spr != nullptr) {
    this->add(spr);
  }
}

void Renderer::add(SpriteRenderComponent *spr) {
  bool added = false;
  for (RenderBatch *batch : batches) {
    if (batch->hasRoom()) {
      batch->addSprite(spr);
      added = true;
      break;
    }
  }

  if (!added) {
    RenderBatch *newBatch = new RenderBatch(1000);
    newBatch->start();
    batches.push_back(newBatch);
    newBatch->addSprite(spr);
  }
}

void Renderer::render() {
  for (RenderBatch *batch : batches) {
    batch->render();
  }
}
