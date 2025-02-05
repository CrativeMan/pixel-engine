#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture {
public:
  unsigned int id;
	Texture(std::string path);
private:
	std::string path;
};

#endif //TEXTURE_HPP
