#ifndef SkyboxTechnique_h
#define SkyboxTechnique_h
#include "../../Lighting/Technique.h"
#include <glm/gtc/type_ptr.hpp>


class SkyboxTechnique : public Technique
{
	GLuint m_WVPLocation;
	GLuint m_textureLocation;

public:
	SkyboxTechnique();
	~SkyboxTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & matrix);
	void setTextureUnit(unsigned int textureUnit);
};
#endif
