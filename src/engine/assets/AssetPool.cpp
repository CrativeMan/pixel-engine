#include "AssetPool.hpp"
#include "../config.h"
#include "Spritesheet.hpp"
#include "Texture.hpp"
#include <filesystem>
#include <unordered_map>

std::unordered_map<std::string, Shader *> AssetPool::shaders;
std::unordered_map<std::string, Texture *> AssetPool::textures;
std::unordered_map<std::string, Spritesheet *> AssetPool::spriteSheets;

std::string AssetPool::getAssetPath(const std::string &asset) {
  return std::string(ASSETS_PATH) + "/" + asset;
}

Shader *AssetPool::getShader(const std::string &vertexPath,
                             const std::string &fragmentPath) {
  std::filesystem::path vfile(getAssetPath(vertexPath));
  std::filesystem::path ffile(getAssetPath(vertexPath));

  std::string absolutePath = vfile.string() + ffile.string();

  auto it = shaders.find(absolutePath);
  if (it != shaders.end())
    return it->second;

  Shader *shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
  AssetPool::shaders[absolutePath] = shader;
  return shader;
}

Texture *AssetPool::getTexture(const std::string &resourceName) {
  std::filesystem::path file(getAssetPath(resourceName));
  std::string absolutePath = file.string();

  auto it = textures.find(absolutePath);
  if (it != textures.end())
    return it->second;

  Texture *texture = new Texture();
  texture->init(resourceName);
  AssetPool::textures[absolutePath] = texture;
  return texture;
}

void AssetPool::addSpriteSheet(const std::string &resourceName,
                               std::shared_ptr<Spritesheet> spritesheet) {
  std::filesystem::path file(getAssetPath(resourceName));
  std::string absolutePath = file.string();

  if (spriteSheets.find(absolutePath) == spriteSheets.end()) {
    Spritesheet *sps = spritesheet.get();
    spriteSheets[absolutePath] = sps;
  }
}

Spritesheet *AssetPool::getSpritesheet(const std::string &resourceName) {
  std::filesystem::path file(getAssetPath(resourceName));
  std::string absolutePath = file.string();

  auto it = spriteSheets.find(absolutePath);
  if (it == spriteSheets.end())
    return nullptr;

  return it->second;
}
