#ifndef LightingTechnique_h
#define LightingTechnique_h
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"
#include "Technique.h"
struct DirectionalLight
{
	glm::vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
	glm::vec3 direction;
};

class LightingTechnique : public Technique
{
	GLuint m_WVPLocation;
	GLuint m_worldMatrixLocation;
	GLuint m_samplerLocation;
	struct
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
		GLuint direction;
	} m_dirLightLocation;
public:
	LightingTechnique();
	virtual ~LightingTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & WVP);
	void setWorldMatrix(const glm::mat4 & world);
	void setTextureUnit(unsigned int textureUnit);
	void setDirectionalLight(const DirectionalLight & light);
};
#endif