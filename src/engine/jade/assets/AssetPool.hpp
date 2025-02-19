#ifndef ASSETPOOL_HPP
#define ASSETPOOL_HPP

#include "Shader.hpp"
#include <string>
#include <unordered_map>

class AssetPool {
public:
  AssetPool() {}
  static Shader *getShader(const std::string &vertexPath,
                           const std::string &fragmentPath);

private:
  static std::unordered_map<std::string, Shader *> shaders;
};

#endif // ASSETPOOL_HPP
