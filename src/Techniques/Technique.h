#ifndef Technique_h
#define Technique_h
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>
#include "Shader.h"

class Technique
{
  GLuint m_shaderProgram;
	typedef std::list<GLuint> shaderObjList;
	shaderObjList m_shaderObjList;

protected:
	bool addShader( Shader::ShaderType shaderType, const std::string filename);
	bool finalize();
	GLint getUniformLocation(const char* pUniformName);

public:
	Technique();
	~Technique();

	virtual bool init();
	void enable();
};
#endif
