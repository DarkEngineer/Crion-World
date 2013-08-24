#ifndef CubemapTexture_h
#define CubemapTexture_h
#include "../../Texture/Texture.h"
#include <FreeImage/FreeImage.h>
#include <memory>
#include <sstream>

class CubemapTexture
{
	std::string m_fileName[6];
	GLuint m_cubePlanes[6];
	GLuint m_textureObject;

	unsigned int getWidth();
	unsigned int getHeight();

public:
	
	CubemapTexture();
	CubemapTexture(const std::string & directory, const std::string & posXFilename, 
		const std::string & negXFilename, const std::string & posYFilename, 
		const std::string & negYFilename, const std::string & posZFilename, 
		const std::string & negZFilename);
	/*
	CubemapTexture(const char * directory, const char * posXFilename, 
		const char * negXFilename, const char * posYFilename,
		const char * negYFilename, const char * posZFilename,
		const char * negZFilename);
		*/
	~CubemapTexture();

	bool load();
	
	void bind(GLenum textureUnit);
};

#endif