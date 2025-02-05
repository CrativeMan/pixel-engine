#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>
#include <string>

class Shader {
public:
  unsigned int id;
  Shader();
  void init(const char *vertex, const char *fragment);
  void shutdown();
  void attach();
  void detach();

  void setInt(std::string name, int value);
  void setFloat(std::string name, float value);
  void setVec3(std::string name, glm::vec3 value);
  void setVec4(std::string name, glm::vec4 value);
  void setMat4(std::string name, glm::mat4 value);

private:
  const char *vertex;
  const char *fragment;
};

#endif // SHADER_HPP
