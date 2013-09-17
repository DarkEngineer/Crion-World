#include "Texture.h"
#include "glFreeImage.h"

	void checkerror()
{
	GLenum string = glGetError();
	std::cout << "Fatail error: " << gluErrorString(string) << std::endl;
}

Texture::Texture()
	: t_Texture( 0 )
	{
	}

Texture::Texture(GLenum textureTarget, const std::string & filename)
	: t_Texture( 0 )
{
	m_textureTarget = textureTarget;
	m_filename = filename;
}
bool Texture::Load()
{
	glFreeImage * FreeImage = new glFreeImage();
	if( !FreeImage->Load(m_filename) )
		return false;
	//load image using FI libs.
	
	glGenTextures(1, &t_Texture);
	glBindTexture(m_textureTarget, t_Texture);
	//Initialize texture with image data
	if(FreeImage->BitsOnPixel() == 3) // if image has 3 bits per pixel
		glTexImage2D(m_textureTarget, 0, GL_RGB, FreeImage->Width(), FreeImage->Height(), 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage->Bits());
	else // if image has 4 bits per pixel
		glTexImage2D(m_textureTarget, 0, GL_RGBA, FreeImage->Width(), FreeImage->Height(), 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage->Bits());

	// min and mag filters
	glTexParameteri( m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri( m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri( m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	
	return true;
}

bool Texture::LoadMipMaps( const std::string & s_Filename)
{
	glFreeImage FreeImage;
	if( !FreeImage.Load( s_Filename ) )
		return false;

	glGenTextures( 1, &t_Texture ); // generate texture name

	glBindTexture( GL_TEXTURE_2D, t_Texture ); // Bind texture name

	//make mipmaps
	// min and mag filters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	return true;
}

void Texture::Bind(GLenum textureUnit) const
{
	glActiveTexture(textureUnit);
	glBindTexture(m_textureTarget, t_Texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, & t_Texture);
}