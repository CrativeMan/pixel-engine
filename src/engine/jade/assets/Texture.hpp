#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture {
public:
  unsigned int id;
  int width, height, nrChannels;
  Texture() {}
  Texture(std::string path);
  void init(std::string path);

  int getWidth() { return this->width; }
  int getHeight() { return this->height; }

private:
  std::string path;
};

#endif // TEXTURE_HPP
