#include "FreeImage\FreeImage.h"
#include "includes.h"
// Made by Dark Engineer

// class for loading an image from disk
class glFreeImage
{
  FIBITMAP * t_Image;
	public:
		glFreeImage();
		~glFreeImage();
			
	bool Load( const std::string & s_Filename ); // load a new image file

	// function are don't modify anyting
	unsigned int Width() const;	// loading image's width
	unsigned int Height() const; // loading image's height
	unsigned int BitsOnPixel() const; // bits per pixel
	const BYTE * Bits() const;
	void Unload(); // unload an image

};

// class for creating texture opengl textures
class glFITexture
{
	GLuint t_Texture;
	public:
		glFITexture();

		bool Load( const std::string & s_Filename ); // loading texture
		bool LoadMipMaps( const std::string & s_Filename ); // loading texture with mipmaps
		void Bind() const;
};

