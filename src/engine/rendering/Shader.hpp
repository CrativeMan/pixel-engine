#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
  unsigned int id;
	Shader();
	void init(const char *vertex, const char *fragment);
	void shutdown();
	void bind();
private:
	const char *vertex;
	const char *fragment;
};

#endif //SHADER_HPP
