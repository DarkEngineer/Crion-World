#include "LightingTechnique.h" 

LightingTechnique::LightingTechnique()
{
}

LightingTechnique::~LightingTechnique()
{
}
bool LightingTechnique::init()
{
	if(!Technique::init())
		return false;

	if(!addShader("shaders/vs_texture.glsl", Shader::VERTEX_SHADER))
		return false;

	if(!addShader("shaders/light_fs.glsl", Shader::FRAGMENT_SHADER))
		return false;

	if(!finalize())
		return false;
	glBindFragDataLocation(getShaderProg(), 0, "FragColor");

	m_WVPLocation = getUniformLocation("gWorld");
	m_samplerLocation = getUniformLocation("gSampler");
	m_dirLightColorLocation = getUniformLocation("gDirectionalLight.color");
	m_dirLightAmbientIntensityLocation = getUniformLocation("gDirectionalLight.ambientIntensity");	

	if(m_WVPLocation == -1 || m_samplerLocation == -1 || m_dirLightColorLocation == -1 || m_dirLightAmbientIntensityLocation == -1)
		return false;

	return true;
}

void LightingTechnique::setWVP(const glm::mat4 & WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, glm::value_ptr(WVP));
}

void LightingTechnique::setDirectionalLight(const DirectionalLight & Light)
{
	glUniform3f(m_dirLightColorLocation, Light.color.x, Light.color.y, Light.color.z);
	glUniform1f(m_dirLightAmbientIntensityLocation, Light.ambientIntensity);
}