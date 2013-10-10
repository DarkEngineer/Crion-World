#ifndef LandscapeTechnique_h
#define LandscapeTechnique_h
#include "../Shader/Shader.h"
#include "../Lighting/Technique.h"
#include <glm/gtc/type_ptr.hpp>

class LandscapeTechnique : public Technique
{
	GLuint m_WVPLocation;
	std::vector <GLuint> m_texturesLocation;

	bool loadMatrixLocation();
	bool loadTexturesLocation();

public:
	LandscapeTechnique();
	virtual ~LandscapeTechnique();

	virtual bool init();

	void setWVP(const glm::mat4 & matrix);
	void setTexture(unsigned int & texture); // use ONLY if heightmap has only 1 texture unit
	void setTexture(unsigned int & texture, int num);
};

#endif