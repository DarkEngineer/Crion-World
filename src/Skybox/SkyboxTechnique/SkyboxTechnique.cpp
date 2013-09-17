#include "SkyboxTechnique.h"

SkyboxTechnique::SkyboxTechnique()
{
}

bool SkyboxTechnique::init()
{
	if(!Technique::init())
		return false;

	if(!addShader("shaders/skyboxvs.glsl", Shader::VERTEX_SHADER))
		return false;

	if(!addShader("shaders/skyboxfs.glsl", Shader::FRAGMENT_SHADER))
		return false;

	if(!finalize())
		return false;

	m_WVPLocation = getUniformLocation("gWVP");
	m_textureLocation = getUniformLocation("gCubemapTexture");

	if(m_WVPLocation == -1 ||
		m_textureLocation == -1)
		return false;

	return true;
}

void SkyboxTechnique::setWVP(const glm::mat4 & matrix)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void SkyboxTechnique::setTextureUnit(unsigned int textureUnit)
{
	glUniform1i(m_textureLocation, textureUnit);
}

SkyboxTechnique::~SkyboxTechnique()
{
}