#ifndef LandscapeTechnique_h
#define LandscapeTechnique_h
#include "../Shader/Shader.h"
#include "../Lighting/Technique.h"
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

class LandscapeTechnique : public Technique
{
	GLuint m_WVPLocation;
	GLuint m_textureLocation;

	bool loadMatrixLocation();
	bool loadTexturesLocation();

public:
	LandscapeTechnique();
	virtual ~LandscapeTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & matrix);
	void setTextureUnit(unsigned int & texture);
};

#endif