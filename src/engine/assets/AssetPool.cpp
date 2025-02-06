#include "AssetPool.hpp"
#include "Spritesheet.hpp"
#include "Texture.hpp"
#include <filesystem>
#include <unordered_map>

std::unordered_map<std::string, Shader *> AssetPool::shaders;
std::unordered_map<std::string, Texture *> AssetPool::textures;
std::unordered_map<std::string, Spritesheet *> AssetPool::spriteSheets;

Shader *AssetPool::getShader(const std::string &vertexPath,
                             const std::string &fragmentPath) {
  std::filesystem::path vfile(vertexPath);
  std::filesystem::path ffile(vertexPath);

  std::string absolutePath = vfile.string() + ffile.string();

  auto it = shaders.find(absolutePath);
  if (it != shaders.end())
    return it->second;

  // TODO this is wrong don't do that whyyyy
  Shader *shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
  AssetPool::shaders[absolutePath] = shader;
  return shader;
}

Texture *AssetPool::getTexture(const std::string &resourceName) {
  std::filesystem::path file(resourceName);
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
  std::filesystem::path file(resourceName);
  std::string absolutePath = file.string();

  if (spriteSheets.find(absolutePath) == spriteSheets.end()) {
    Spritesheet *sps = spritesheet.get();
    spriteSheets[absolutePath] = sps;
  }
}

Spritesheet *AssetPool::getSpritesheet(const std::string &resourceName) {
  std::filesystem::path file(resourceName);
  std::string absolutePath = file.string();

  auto it = spriteSheets.find(absolutePath);
  if (it == spriteSheets.end())
    return nullptr;

  return it->second;
}
