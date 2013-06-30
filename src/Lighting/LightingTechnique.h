#ifndef LightingTechnique_h
#define LightingTechnique_h
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"
#include "Technique.h"


struct BaseLight
{
	glm::vec3 color;
	float ambientIntensity;
	float diffuseIntensity;

	BaseLight();
};

struct DirectionalLight : public BaseLight
{
	glm::vec3 direction;

	DirectionalLight();
};


struct PointLight : public BaseLight
{
	glm::vec3 position;

	struct
	{
		float constant;
		float linear;
		float exp;
	} attentuation;

	PointLight();
};

class LightingTechnique : public Technique
{
	static const unsigned int MAX_POINT_LIGHTS = 2;

	GLuint m_WVPLocation;
	GLuint m_worldMatrixLocation;
	GLuint m_samplerLocation;
	GLuint m_eyeWorldLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;
	GLuint m_numPointLightsLocation;
	struct
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
		GLuint direction;
	} m_dirLightLocation;

	struct
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
		GLuint position;
		
		struct
		{
			GLuint constant;
			GLuint linear;
			GLuint exp;
		} attentuation;
	} m_pointLightsLocation[MAX_POINT_LIGHTS];

	void loadLightLocation();
	void loadSpecularEffectLocation();
public:
	LightingTechnique();
	virtual ~LightingTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & WVP);
	void setWorldMatrix(const glm::mat4 & world);
	void setTextureUnit(unsigned int textureUnit);
	void setDirectionalLight(const DirectionalLight & light);
	void setPointLights(unsigned int lightsNumber, const PointLight* light);
	void setEyeWorldPos(const glm::vec3 & pos);
	void setSpecularIntensity(float intensity);
	void setSpecularPower(float power);
};
#endif