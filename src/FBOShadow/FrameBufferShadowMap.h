#ifndef FrameBufferShadowMap_h
#define FrameBufferShadowMap_h
#include <iostream>
#include <GL/glew.h>
class ShadowMap
{
	GLuint m_fbo;
	GLuint m_shadowMap;
public:
	ShadowMap();
	virtual ~ShadowMap();

	bool initShadow(unsigned int windowWidth, unsigned int windowHeight);
	void bindForWriting();
	void bindForReading(GLenum textureUnit);
};
#endif