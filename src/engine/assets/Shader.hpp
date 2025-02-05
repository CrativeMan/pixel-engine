#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
  unsigned int id;
	Shader();
	void init(const char *vertex, const char *fragment);
	void shutdown();
	void attach();
	void detach();

	void setInt();
	void setFloat();
	void setVec3();
	void setVec4();
	void setMat4();
private:
	const char *vertex;
	const char *fragment;
};

#endif //SHADER_HPP
