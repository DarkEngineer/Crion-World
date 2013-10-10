#include "LandscapeTechnique.h"

LandscapeTechnique::LandscapeTechnique()
{
}

LandscapeTechnique::~LandscapeTechnique()
{
}

bool LandscapeTechnique::init()
{
	if(!Technique::init())
		return false;

	if(!addShader("heightmap_vs.glsl", Shader::VERTEX_SHADER))
		return false;

	if(!addShader("heightmap_fs.glsl", Shader::FRAGMENT_SHADER))
		return false;

	if(!finalize())
		return false;

	return true;
}

bool LandscapeTechnique::loadMatrixLocation()
{
	m_WVPLocation = getUniformLocation("gWVP");

	if(m_WVPLocation == -1)
		return false;

	return true;
}

bool LandscapeTechnique::loadTexturesLocation()
{
	std::vector <GLuint>::iterator t_counter;
	for(t_counter = m_texturesLocation.begin(); t_counter != m_texturesLocation.end(); t_counter++)
	{
		if(* t_counter == -1)
			return false;
		else 
			return true;
	}
}

void LandscapeTechnique::setWVP(const glm::mat4 & matrix)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LandscapeTechnique::setTexture(unsigned int & texture)
{
	if(m_texturesLocation.size() == 1)
		glUniform1i(m_texturesLocation[0], texture);
	else
		std::cout << "Heightmap has more than 1 texture! Use another function" << std::endl;
}

void LandscapeTechnique::setTexture(unsigned int & texture, int num)
{
	glUniform1i(m_texturesLocation[num], texture);
}
