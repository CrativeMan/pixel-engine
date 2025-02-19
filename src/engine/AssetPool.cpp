#include <filesystem>
#include <jade/assets/AssetPool.hpp>
#include <system/System.hpp>
#include <unordered_map>

std::unordered_map<std::string, Shader *> AssetPool::shaders;

Shader *AssetPool::getShader(const std::string &vertexPath,
                             const std::string &fragmentPath) {
  std::filesystem::path vfile(sys::getAssetPath(vertexPath));
  std::filesystem::path ffile(sys::getAssetPath(vertexPath));

  std::string absolutePath = vfile.string() + ffile.string();

  auto it = shaders.find(absolutePath);
  if (it != shaders.end())
    return it->second;

  Shader *shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
  AssetPool::shaders[absolutePath] = shader;
  return shader;
}