#ifndef Shader_h
#define Shader_h

#include "../includes.h"


class Shader
{
  std::string source;
	GLuint shader;
	
	
public:
	// shader types
	enum ShaderType
	{
		VERTEX_SHADER = 1,
		FRAGMENT_SHADER = 2,
		GEOMETRY_SHADER = 3,
		TESS_CONTROL_SHADER = 4,
		TESS_EVALUATION_SHADER = 5,
	} objShaderType;
	Shader();
	GLuint getShader();
	GLuint createShaderFromFile(std::string name, ShaderType type);
	void attachShader( GLuint program );
	std::string loadShaderFile(const std::string fileName);
	void getShaderLogInfo( GLuint shader );
	void getProgramLogInfo( GLuint program );
	void DelShader();
	virtual ~Shader();
};
#endif
