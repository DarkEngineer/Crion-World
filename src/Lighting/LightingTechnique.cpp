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

SpotLight::SpotLight()
{
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	cutoff = 0.0f;
};

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
	m_lightMatrixLocation = getUniformLocation("gLightMatrix");
	m_normalMatrixLocation = getUniformLocation("gNormalMatrix");
	m_samplerLocation = getUniformLocation("gSampler");
	if(!loadLightLocation())
		return false;
	if(!loadSpecularEffectLocation())
		return false;
	if(!loadPointLightLocation())
		return false;
	if(!loadSpotLightLocation())
		return false;
	if(!loadShadowMapLocation())
		return false;

	if(m_WVPLocation == -1 || 
		m_worldMatrixLocation == -1 || 
		m_lightMatrixLocation == -1 ||
		m_samplerLocation == -1 || 
		m_normalMatrixLocation == -1)
		return false;

	return true;
}

void LightingTechnique::setWVP(const glm::mat4 & WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(WVP));
}


void LightingTechnique::setLightMatrix(const glm::mat4 & lightMatrix)
{
	glUniformMatrix4fv(m_lightMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightMatrix));
}

void LightingTechnique::setWorldMatrix(const glm::mat4 & world)
{
	glUniformMatrix4fv(m_worldMatrixLocation, 1, GL_FALSE, glm::value_ptr(world));
}

void LightingTechnique::setNormalMatrix(const glm::mat3 & normalMatrix)
{
	glUniformMatrix3fv(m_normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void LightingTechnique::setTextureUnit(unsigned int textureUnit)
{
	glUniform1i(m_samplerLocation, textureUnit);
}

void LightingTechnique::setShadowMapTextureUnit(unsigned int textureUnit)
{
	glUniform1i(m_shadowMapLocation, textureUnit);
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

bool LightingTechnique::loadLightLocation()
{
	m_dirLightLocation.color = getUniformLocation("gDirectionalLight.base.color");
	m_dirLightLocation.ambientIntensity = getUniformLocation("gDirectionalLight.base.ambientIntensity");	
	m_dirLightLocation.diffuseIntensity = getUniformLocation("gDirectionalLight.base.diffuseIntensity");
	m_dirLightLocation.direction = getUniformLocation("gDirectionalLight.direction");

	if(m_dirLightLocation.color == -1 ||
		m_dirLightLocation.ambientIntensity == -1 ||
		m_dirLightLocation.diffuseIntensity == -1 ||
		m_dirLightLocation.direction == -1)
		return false;

	return true;
}

bool LightingTechnique::loadSpecularEffectLocation()
{
	m_eyeWorldLocation = getUniformLocation("gEyeWorldPos");
	m_matSpecularIntensityLocation = getUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = getUniformLocation("gSpecularPower");

	if(m_eyeWorldLocation == -1 ||
		m_matSpecularIntensityLocation == -1 ||
		m_matSpecularPowerLocation == -1)
		return false;

	return true;
}


bool LightingTechnique::loadPointLightLocation()
{
	m_numPointLightsLocation = getUniformLocation("gNumPointLights");

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::string lightString = "gPointLights[";
		std::ostringstream count;
		count << i;
		lightString = lightString + count.str() + "]";
		m_pointLightsLocation[i].color = getUniformLocation(lightString + ".base.color");
		m_pointLightsLocation[i].ambientIntensity = getUniformLocation(lightString + ".base.ambientIntensity");
		m_pointLightsLocation[i].diffuseIntensity = getUniformLocation(lightString + ".base.diffuseIntensity");
		m_pointLightsLocation[i].position = getUniformLocation(lightString + ".position");
		m_pointLightsLocation[i].attentuation.constant = getUniformLocation(lightString + ".attentuation.constant");
		m_pointLightsLocation[i].attentuation.linear = getUniformLocation(lightString + ".attentuation.linear");
		m_pointLightsLocation[i].attentuation.exp = getUniformLocation(lightString + ".attentuation.exp");

		if(m_pointLightsLocation[i].color == -1 ||
			m_pointLightsLocation[i].ambientIntensity == -1 ||
			m_pointLightsLocation[i].diffuseIntensity == -1 ||
			m_pointLightsLocation[i].position == -1 ||
			m_pointLightsLocation[i].attentuation.constant == -1 ||
			m_pointLightsLocation[i].attentuation.linear == -1 ||
			m_pointLightsLocation[i].attentuation.exp == -1)
			return false;
	}

	if(m_numPointLightsLocation == -1)
		return false;

	return true;
}

bool LightingTechnique::loadSpotLightLocation()
{
	m_numSpotLightsLocation = getUniformLocation("gNumSpotLights");

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		std::string lightString = "gSpotLights[";
		std::ostringstream count;
		count << i; 
		lightString = lightString + count.str() + "]";
		m_spotLightLocation[i].color = getUniformLocation(lightString + ".base.base.color");
		m_spotLightLocation[i].ambientIntensity = getUniformLocation(lightString + ".base.base.ambientIntensity");
		m_spotLightLocation[i].diffuseIntensity = getUniformLocation(lightString + ".base.base.diffuseIntensity");
		m_spotLightLocation[i].position = getUniformLocation(lightString + ".base.position");
		m_spotLightLocation[i].attentuation.constant = getUniformLocation(lightString + ".base.attentuation.constant");
		m_spotLightLocation[i].attentuation.linear = getUniformLocation(lightString + ".base.attentuation.linear");
		m_spotLightLocation[i].attentuation.exp = getUniformLocation(lightString + ".base.attentuation.exp");
		m_spotLightLocation[i].direction = getUniformLocation(lightString + ".direction");
		m_spotLightLocation[i].cutoff = getUniformLocation(lightString + ".cutoff");

		if(m_spotLightLocation[i].color == -1 ||
			m_spotLightLocation[i].ambientIntensity == -1 ||
			m_spotLightLocation[i].diffuseIntensity == -1 ||
			m_spotLightLocation[i].position == -1 ||
			m_spotLightLocation[i].attentuation.constant == -1 ||
			m_spotLightLocation[i].attentuation.linear == -1 ||
			m_spotLightLocation[i].attentuation.exp == -1 ||
			m_spotLightLocation[i].direction == -1 ||
			m_spotLightLocation[i].cutoff == -1)
			return false;

	}

	if(m_numSpotLightsLocation == -1)
		return false;

	return true;
}

bool LightingTechnique::loadShadowMapLocation()
{
	m_shadowMapLocation = getUniformLocation("gShadowMap");

	if(m_shadowMapLocation == -1)
		return false;

	return true;
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

void LightingTechnique::setSpotLights(unsigned int lightsNumber, const SpotLight * light)
{
	glUniform1i(m_numSpotLightsLocation, lightsNumber);

	for(int i = 0; i < lightsNumber; i++)
	{
		glUniform3f(m_spotLightLocation[i].color, light[i].color.x, light[i].color.y, light[i].color.z);
		glUniform1f(m_spotLightLocation[i].ambientIntensity, light[i].ambientIntensity);
		glUniform1f(m_spotLightLocation[i].diffuseIntensity, light[i].diffuseIntensity);
		glUniform3f(m_spotLightLocation[i].position, light[i].position.x, light[i].position.y, light[i].position.z);
		glm::vec3 direction = glm::normalize(light[i].direction);
		glUniform3f(m_spotLightLocation[i].direction, direction.x, direction.y, direction.z);
		glUniform1f(m_spotLightLocation[i].cutoff, cosf(glm::radians(light[i].cutoff)));
		glUniform1f(m_spotLightLocation[i].attentuation.constant, light[i].attentuation.constant);
		glUniform1f(m_spotLightLocation[i].attentuation.linear, light[i].attentuation.linear);
		glUniform1f(m_spotLightLocation[i].attentuation.exp, light[i].attentuation.exp);
	}
}