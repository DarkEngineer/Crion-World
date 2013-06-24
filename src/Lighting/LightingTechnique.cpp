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

	m_WVPLocation = getUniformLocation("gWVP");
	m_worldMatrixLocation = getUniformLocation("gWorld");
	m_samplerLocation = getUniformLocation("gSampler");
	m_dirLightLocation.color = getUniformLocation("gDirectionalLight.color");
	m_dirLightLocation.ambientIntensity = getUniformLocation("gDirectionalLight.ambientIntensity");	
	m_dirLightLocation.diffuseIntensity = getUniformLocation("gDirectionalLight.diffuseIntensity");
	m_dirLightLocation.direction = getUniformLocation("gDirectionalLight.direction");
	m_eyeWorldLocation = getUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation = getUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = getUniformLocation("gSpecularPower");

	if(m_WVPLocation == -1 || m_worldMatrixLocation == -1 || m_samplerLocation == -1 || m_dirLightLocation.color == -1 || 
		m_dirLightLocation.ambientIntensity == -1 || m_dirLightLocation.diffuseIntensity == -1 || m_dirLightLocation.direction == -1 ||
		m_eyeWorldLocation == -1 || m_matSpecularIntensityLocation == -1 || m_matSpecularPowerLocation == -1)
		return false;

	return true;
}

void LightingTechnique::setWVP(const glm::mat4 & WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(WVP));
}

void LightingTechnique::setWorldMatrix(const glm::mat4 & world)
{
	glUniformMatrix4fv(m_worldMatrixLocation, 1, GL_FALSE, glm::value_ptr(world));
}

void LightingTechnique::setDirectionalLight(const DirectionalLight & Light)
{
	glUniform3f(m_dirLightLocation.color, Light.color.x, Light.color.y, Light.color.z);
	glUniform1f(m_dirLightLocation.ambientIntensity, Light.ambientIntensity);
	glm::vec3 direction = Light.direction;
	direction = glm::normalize(direction);
	glUniform3f(m_dirLightLocation.direction, direction.x, direction.y, direction.z);
	glUniform1f(m_dirLightLocation.diffuseIntensity, Light.diffuseIntensity);
}

void LightingTechnique::setEyeWorldPos(const glm::vec3 & pos)
{
	glUniform3f(m_eyeWorldLocation, pos.x, pos.y, pos.z);
}

void LightingTechnique::setSpecularIntensity(float intensity)
{
	glUniform1f(m_matSpecularIntensityLocation, intensity);
}

void LightingTechnique::setSpecularPower(float power)
{
	glUniform1f(m_matSpecularPowerLocation, power);
}