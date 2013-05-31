#ifndef LightingTechnique_h
#define LightingTechnique_h
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"
#include "Technique.h"
struct DirectionalLight
{
	glm::vec3 color;
	float ambientIntensity;
};

class LightingTechnique : public Technique
{
	GLuint m_WVPLocation;
	GLuint m_samplerLocation;
	GLuint m_dirLightColorLocation;
	GLuint m_dirLightAmbientIntensityLocation;

public:
	LightingTechnique();
	virtual ~LightingTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & WVP);
	void setTextureUnit(unsigned int textureUnit);
	void setDirectionalLight(const DirectionalLight & light);
};
#endif