#include "ShadowMapTechnique.h"

ShadowMapTechnique::ShadowMapTechnique()
{
}

bool ShadowMapTechnique::init()
{
	if(!Technique::init())
		return false;

	if(!addShader("shaders/shadowmapvs.glsl", Shader::VERTEX_SHADER))
		return false;

	if(!addShader("shaders/shadowMapfs.glsl", Shader::FRAGMENT_SHADER))
		return false;

	if(!finalize())
		return false;

	m_WVPLocation = getUniformLocation("gWVP");
	m_textureLocation = getUniformLocation("gShadowMap");

	if(m_WVPLocation == -1 ||
		m_textureLocation == -1)
		return false;

	return true;
}

void ShadowMapTechnique::setMatrix(const glm::mat4 & WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(WVP));
}

void ShadowMapTechnique::setTextureUnit(unsigned int textureUnit)
{
	glUniform1i(m_textureLocation, textureUnit);
}

ShadowMapTechnique::~ShadowMapTechnique()
{
	delete & m_WVPLocation;
	delete & m_textureLocation;
}
