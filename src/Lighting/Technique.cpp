#include "Technique.h"

Technique::Technique()
{
	m_shaderProg = 0;
}

Technique::~Technique()
{
	for( ShaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++)
	{
		glDeleteShader(it->getShader());
	}
	if(m_shaderProg != 0)
	{
		glDeleteProgram(m_shaderProg);
		m_shaderProg = 0;
	}
}

bool Technique::init()
{
	m_shaderProg = glCreateProgram();

	if( m_shaderProg == 0)
	{
		std::cout << "Error creating shader program" << std::endl;
		return false;
	}

	return true;
}

bool Technique::addShader(const char* filename, Shader::ShaderType type)
{
	Shader * t_shader;
	t_shader = new Shader;
	t_shader->createShaderFromFile(filename, type);
	m_shaderObjList.push_back(*t_shader);

	GLint success;
	glGetShaderiv(t_shader->getShader(), GL_COMPILE_STATUS, &success);
	if(!success)
		return false;

	t_shader->attachShader(m_shaderProg);
	delete t_shader;
	return true;

	
}

bool Technique::finalize()
{
	Shader * t_shader;
	t_shader = new Shader;
	glLinkProgram(m_shaderProg);

	for(ShaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++)
		glDeleteShader(it->getShader());

	m_shaderObjList.clear();

	return true;
}

void Technique::enable()
{
	glUseProgram(m_shaderProg);
}

GLint Technique::getUniformLocation(const char* uniformName)
{
	GLint location = glGetUniformLocation(m_shaderProg, uniformName);

	if(location == -1)
		std::cout << "Wrong uniform location: " << uniformName << std::endl;

	return location;
}

GLuint Technique::getShaderProg()
{
	return m_shaderProg;
}

