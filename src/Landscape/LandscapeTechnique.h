#ifndef LandscapeTechnique_h
#define LandscapeTechnique_h
#include "../Shader/Shader.h"
#include "../Lighting/Technique.h"

class LandscapeTechnique : public Technique
{
	GLuint m_WVPLocation;
	std::vector <GLuint> m_texturesLocation;

public:
	LandscapeTechnique();
	virtual ~LandscapeTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & matrix);
	void setTexture(unsigned int & texture);
};

#endif