#include "loadImage.h"

glFreeImage::glFreeImage()
  :	t_Image( 0 )
	{
	}

bool glFreeImage::Load( const std::string & s_Filename )
{
	//unloading first for save
	Unload();

	FREE_IMAGE_FORMAT FreeImageFormat = FreeImage_GetFileType( s_Filename.c_str(), 0 );

	if( FreeImageFormat == FIF_UNKNOWN )
		FreeImageFormat = FreeImage_GetFIFFromFilename( s_Filename.c_str() );

	if( FreeImageFormat == FIF_UNKNOWN )
		return false;

	if( FreeImage_FIFSupportsReading( FreeImageFormat ) )
		t_Image = FreeImage_Load( FreeImageFormat, s_Filename.c_str() );

	return t_Image != 0;
}

unsigned int glFreeImage::Width() const
{
	return  t_Image ? FreeImage_GetWidth( t_Image ): 0;
}

unsigned int glFreeImage::Height() const
{
	return t_Image ? FreeImage_GetHeight( t_Image ): 0;
}

unsigned int glFreeImage::BitsOnPixel() const
{
	return t_Image ? FreeImage_GetBPP( t_Image ): 0;
}

const BYTE * glFreeImage::Bits() const
{
	return t_Image ? FreeImage_GetBits( t_Image ): 0;
}
	
void glFreeImage::Unload()
{
	if( t_Image )
	{
		FreeImage_Unload( t_Image );
		t_Image = 0;
	}
}

glFreeImage::~glFreeImage()
{
	Unload();
}

glFITexture::glFITexture()
	: t_Texture( 0 )
	{
	}

bool glFITexture::Load( const std::string & s_Filename )
{
	//load image using FI libs.
	glFreeImage FreeImage;
	if( !FreeImage.Load( s_Filename ) )
		return false;

	glGenTextures( 1, &t_Texture );// generate texture name

	glBindTexture( GL_TEXTURE_2D, t_Texture );// Bind texture name

	//Initialize texture with image data
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, FreeImage.Width(), FreeImage.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, FreeImage.Bits() );

	// min and mag filters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	return true;
}

bool glFITexture::LoadMipMaps( const std::string & s_Filename)
{
	glFreeImage FreeImage;
	if( !FreeImage.Load( s_Filename ) )
		return false;

	glGenTextures( 1, &t_Texture ); // generate texture name

	glBindTexture( GL_TEXTURE_2D, t_Texture ); // Bind texture name

	//make mipmaps
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, FreeImage.Width(), FreeImage.Height(), GL_RGBA, GL_UNSIGNED_BYTE, FreeImage.Bits() );

	
	// min and mag filters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	return true;
}

void glFITexture::Bind() const
{
	glBindTexture( GL_TEXTURE_2D, t_Texture );
}

