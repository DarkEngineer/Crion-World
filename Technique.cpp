#include <iostream>
#include "Technique.h"

Technique::Technique()
{
	m_shaderProgram = 0;
}

Technique::~Technique()
{
	for(shaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++)
		glDeleteShader(*it);
	if(m_shaderProgram != 0)
	{
		glDeleteProgram(m_shaderProgram);
		m_shaderProgram = 0;
	}
}

bool Technique::init()
{
	m_shaderProgram = glCreateProgram();

	if(m_shaderProgram == 0)
	{
		std::cout << "Error creating shader program" << std::endl;
		return false;
	}

	return true;
}

bool Technique::addShader(Shader::ShaderType shaderType, const std::string filename)
{
	Shader shaderObj;
	shaderObj.createShaderFromFile(filename, shaderType);
	if(shaderObj.getShader() == 0)
	{
		std::cout << "Error shader program" << std::endl;
		return false;
	}
	m_shaderObjList.push_back(shaderObj.getShader());
	shaderObj.attachShader(m_shaderProgram);

	return true;
}

bool Technique::finalize()
{
	GLint success = 0;
	GLchar errorLog[1024] = {NULL};

	glLinkProgram( m_shaderProgram );

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if( success == 0 )
	{
		glGetProgramInfoLog(m_shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::cout << "Error linking shader program: " << errorLog << std::endl;
		return false;
	}

	glValidateProgram( m_shaderProgram );
	glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::cout << "Invalid shader program: " << errorLog << std::endl;
		return false;
	}

	for(shaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++)
		glDeleteShader(*it);

	m_shaderObjList.clear();

	return true;
}

void Technique::enable()
{
	glUseProgram(m_shaderProgram);
}

GLint Technique::getUniformLocation(const char* pUniformName)
{
	GLint location = glGetUniformLocation(m_shaderProgram, pUniformName);

	if(location == 0xFFFFFFFF)
	{
		std::cout << "Warning! Unable to get the location of uniform " << pUniformName << std::endl;
	}

	return location;
}