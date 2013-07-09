#include "FrameBufferShadowMap.h"

ShadowMap::ShadowMap()
{
	m_fbo = 0;
	m_shadowMap = 0;
}

bool ShadowMap::initShadow(unsigned int windowWidth, unsigned int windowHeight)
{
	glGenFramebuffers(1, &m_fbo);
	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);
	glDrawBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer error: " << status << std::endl;
		return false;
	}

	return true;
}

void ShadowMap::bindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void ShadowMap::bindForReading(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureUnit);
}

ShadowMap::~ShadowMap()
{
	 if (m_fbo != 0)
        glDeleteFramebuffers(1, &m_fbo);

    if (m_shadowMap != 0) 
        glDeleteTextures(1, &m_shadowMap);
	delete & m_fbo;
	delete & m_shadowMap;
}
