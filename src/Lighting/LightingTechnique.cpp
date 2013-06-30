#include "LightingTechnique.h" 

DirectionalLight::DirectionalLight()
{
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
}

LightingTechnique::LightingTechnique()
{
}

LightingTechnique::~LightingTechnique()
{
}

BaseLight::BaseLight()
{
	color = glm::vec3(0.0f, 0.0f, 0.0f);
	ambientIntensity = 0.0f;
	diffuseIntensity = 0.0f;
}

PointLight::PointLight()
{
	position = glm::vec3(0.0f, 0.0, 0.0f);
	attentuation.constant = 1.0f;
	attentuation.linear = 0.0f;
	attentuation.exp = 0.0f;
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
	loadLightLocation();
	loadSpecularEffectLocation();

	//for (unsigned int i = 0 ; i < sizeof(m_pointLightsLocation)/sizeof(m_pointLightsLocation[0]) ; i++) {
 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
 //       m_pointLightsLocation[i].Color = GetUniformLocation(Name);

 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
 //       m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
 //       m_pointLightsLocation[i].Position = GetUniformLocation(Name);

 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
 //       m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
 //       m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
 //       m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

 //       SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
 //       m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);


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

void LightingTechnique::loadLightLocation()
{
	m_dirLightLocation.color = getUniformLocation("gDirectionalLight.base.color");
	m_dirLightLocation.ambientIntensity = getUniformLocation("gDirectionalLight.base.ambientIntensity");	
	m_dirLightLocation.diffuseIntensity = getUniformLocation("gDirectionalLight.base.diffuseIntensity");
	m_dirLightLocation.direction = getUniformLocation("gDirectionalLight.direction");
}

void LightingTechnique::loadSpecularEffectLocation()
{
	m_eyeWorldLocation = getUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation = getUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = getUniformLocation("gSpecularPower");

}

void LightingTechnique::setPointLights(unsigned int lightsNumber, const PointLight * light)
{
	glUniform1i(m_numPointLightsLocation, lightsNumber);

	for(int i = 0; i < lightsNumber; i++)
	{
		glUniform3f(m_pointLightsLocation[i].color, light[i].color.x, light[i].color.y, light[i].color.z);
		glUniform1f(m_pointLightsLocation[i].ambientIntensity, light[i].ambientIntensity);
		glUniform1f(m_pointLightsLocation[i].diffuseIntensity, light[i].diffuseIntensity);
		glUniform3f(m_pointLightsLocation[i].position, light[i].position.x, light[i].position.y, light[i].position.z);
		glUniform1f(m_pointLightsLocation[i].attentuation.constant, light[i].attentuation.constant);
		glUniform1f(m_pointLightsLocation[i].attentuation.linear, light[i].attentuation.linear);
		glUniform1f(m_pointLightsLocation[i].attentuation.exp, light[i].attentuation.exp);
	}
}