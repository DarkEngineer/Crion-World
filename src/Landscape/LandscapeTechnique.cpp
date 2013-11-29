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

	if(!addShader("shaders/landscape_vs.glsl", Shader::VERTEX_SHADER))
		return false;

	if(!addShader("shaders/landscape_fs.glsl", Shader::FRAGMENT_SHADER))
		return false;

	if(!finalize())
		return false;

	loadMatrixLocation();
	loadTexturesLocation();

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
	m_textureLocation = getUniformLocation("gTexture");

	if(m_textureLocation == -1)
		return false;

	return true;
}

void LandscapeTechnique::setWVP(const glm::mat4 & matrix)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}


void LandscapeTechnique::setTextureUnit(unsigned int texture)
{
	glUniform1i(m_textureLocation, texture);
}
