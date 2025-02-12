#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../../assets/Sprite.hpp"
#include "Transform.hpp"
#include "ecs.hpp"

#include <glm/ext/vector_float4.hpp>
#include <memory>

class SpriteRenderComponent : public Component {
public:
  void start() override;
  void update(float dt) override;
  void imgui() override {}

private:
  bool first = false;
  glm::vec4 color = glm::vec4(1.0f);
  std::unique_ptr<Sprite> sprite;
  Transform lastTransform;
  bool dirty = true;
};

class FontRendererComponenet : public Component {
public:
  void start() override;
  void update(float dt) override;
  void imgui() override {}
};

#endif // __COMPONENT_H__
