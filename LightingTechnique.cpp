#include "LightingTechnique.h"

LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::init()
{
  if(!Technique::init())
		return false;

	if(!addShader( Shader::ShaderType::VERTEX_SHADER, "vslightingtechnique.glsl" ) )
		return false;

	if(!addShader( Shader::ShaderType::FRAGMENT_SHADER, "fslightingtechnique.glsl") )
		return false;

	if(!finalize())
		return false;

	m_WVPLocation = getUniformLocation("gWVP");
	m_samplerLocation = getUniformLocation("gSampler");
	m_dirLightColorLocation = getUniformLocation("gDirectionalLight.Color");
	m_dirLightAmbientIntensityLocation = getUniformLocation("gDirectionalLight.AmbientIntensity");

	if(m_dirLightAmbientIntensityLocation == 0xFFFFFFFF || m_dirLightColorLocation == 0xFFFFFFFF|| m_WVPLocation == 0xFFFFFFFF || m_samplerLocation == 0xFFFFFFFF)
		return false;

	return true;

}

void LightingTechnique::setWVP(const glm::mat4 &WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, &WVP[0][0]);
}

void LightingTechnique::setTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}

void LightingTechnique::setDirectionalLight(const DirectionalLight& light)
{
	glUniform3f(m_dirLightColorLocation, light.color.x, light.color.y, light.color.z);
	glUniform1f(m_dirLightAmbientIntensityLocation, light.ambientIntensity);
}
