#include "glFreeImage.h"

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

