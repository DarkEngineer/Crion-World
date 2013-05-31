#ifndef Technique_h
#define Technique_h
#include <GL/glew.h>
#include <GL\glfw.h>
#include "../shader_manager/Shader.h"
#include <list>
class Technique
{
	GLuint m_shaderProg;

	typedef std::list<Shader> ShaderObjList;
	ShaderObjList m_shaderObjList;


protected:

	bool addShader(const char* filename, Shader::ShaderType type);
	bool finalize();
	GLint getUniformLocation(const char* uniformName);
	GLuint getShaderProg();

public:
	Technique();
	virtual ~Technique();

	virtual bool init();

	void enable();
};
#endif