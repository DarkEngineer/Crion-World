#ifndef Shader_h
#define Shader_h

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <vector>
#include <GL/glfw.h>

enum ShaderType;

class Shader
{
	std::string source;
	GLuint shader;
	void getShaderLogInfo( GLuint shader );
	void getProgramLogInfo( GLuint program );
	std::string loadShaderFile(const std::string fileName);

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
	//create shader from file
	GLuint createShaderFromFile(std::string name, ShaderType type);
	void attachShader( GLuint program );
	
	
	void DelShader();
	virtual ~Shader();
};
#endif