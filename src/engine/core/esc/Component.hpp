#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../../assets/Sprite.hpp"
#include "Transform.hpp"

#include <glm/ext/vector_float4.hpp>
#include <memory>

class Component {
public:
  virtual void start() = 0;
  virtual void update(float dt) = 0;
  virtual void imgui() = 0;
};

class SpriteRenderComponent : public Component {
public:
  void start() override;
  void update(float dt) override;

private:
  glm::vec4 color = glm::vec4(1.0f);
  std::unique_ptr<Sprite> sprite;
  Transform lastTransform;
  bool dirty = true;
};

#endif // __COMPONENT_H__