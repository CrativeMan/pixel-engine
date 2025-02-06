#ifndef ASSETPOOL_HPP
#define ASSETPOOL_HPP

#include "Shader.hpp"
#include "Spritesheet.hpp"
#include "Texture.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class AssetPool {
public:
  AssetPool() {}
  static Shader *getShader(const std::string &vertexPath,
                           const std::string &fragmentPath);
  static Texture *getTexture(const std::string &resourceName);
  static void addSpriteSheet(const std::string &resourceName,
                             std::shared_ptr<Spritesheet> spritesheet);
  static Spritesheet *getSpritesheet(const std::string &resourceName);

private:
  static std::unordered_map<std::string, Shader *> shaders;
  static std::unordered_map<std::string, Texture *> textures;
  static std::unordered_map<std::string, Spritesheet *> spriteSheets;
};

#endif // ASSETPOOL_HPP
