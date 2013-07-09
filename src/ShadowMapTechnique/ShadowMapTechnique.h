#ifndef ShadowMapTechnique_h
#define ShadowMapTechnique_h
#include "../Lighting/Technique.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShadowMapTechnique : public Technique
{
	GLint m_WVPLocation;
	GLint m_textureLocation;
public:
	ShadowMapTechnique();
	~ShadowMapTechnique();
	virtual bool init();

	void setMatrix(const glm::mat4 & WVP);
	void setTextureUnit(unsigned int textureUnit);

};
#endif