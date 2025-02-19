#ifndef LEVELEDITORSCENE_H
#define LEVELEDITORSCENE_H

#pragma once

#include <clue.hpp>
#include <jade/assets/AssetPool.hpp>
#include <jade/core/scene/Scene.hpp>

#include <GL/glew.h>

class LevelEditorScene : public Scene {
public:
  LevelEditorScene();

  ~LevelEditorScene();

  void init() override;

  void update(float deltaTime) override;

  void render(float dt) override;

private:
  unsigned int vao, vbo, ebo;
  Shader *shader;

  void loadResources();
};

#endif
