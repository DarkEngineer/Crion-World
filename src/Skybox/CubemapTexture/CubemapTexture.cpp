#include "CubemapTexture.h"

static GLenum textureSides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
								GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
								GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
								GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
								GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
								GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };


CubemapTexture::CubemapTexture()
{
}

CubemapTexture::CubemapTexture(const std::string & directory, 
							   const std::string & posXFilename, 
							   const std::string & negXFilename, 
							   const std::string & posYFilename, 
							   const std::string & negYFilename, 
							   const std::string & posZFilename, 
							   const std::string & negZFilename)
{
	std::string::const_iterator iter = directory.end();
	iter--;
	
	std::string Dir = (*iter == '/') ? directory : directory + "/";

	m_fileName[0] = Dir + posXFilename;
	m_fileName[1] = Dir + negXFilename;
	m_fileName[2] = Dir + posYFilename;
	m_fileName[3] = Dir + negYFilename;
	m_fileName[4] = Dir + posZFilename;
	m_fileName[5] = Dir + negZFilename;

	for(int i = 0; i < 6; i++)
		std::cout << m_fileName[i] << std::endl;
	m_textureObject = NULL;
}

bool CubemapTexture::load()
{

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	for(int i = 0; i < ARRAYSIZE(m_fileName); i++)
	{
		FREE_IMAGE_FORMAT FreeImageFormat = FreeImage_GetFileType(m_fileName[i].c_str(), 0);

		std::unique_ptr<FIBITMAP> t_Image(new FIBITMAP);

		if( FreeImageFormat == FIF_UNKNOWN )
		FreeImageFormat = FreeImage_GetFIFFromFilename( m_fileName[i].c_str());

		if( FreeImageFormat == FIF_UNKNOWN )
		{
			std::cout << "Unknown " << m_fileName[i] << " format" << std::endl;
			return false;
		}

		if( FreeImage_FIFSupportsReading( FreeImageFormat ) )
		{
			t_Image = std::unique_ptr<FIBITMAP>(FreeImage_Load( FreeImageFormat, m_fileName[i].c_str()));
			std::cout << "Loading: " << m_fileName[i] << std::endl;
		}
		else
			t_Image = std::unique_ptr<FIBITMAP>(FreeImage_Load( FreeImageFormat, "images/default/chessboard.jpg"));
		
		
		glTexImage2D(textureSides[i], 0, GL_RGB, FreeImage_GetWidth(t_Image.get()), FreeImage_GetHeight(t_Image.get()), 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(t_Image.get()));

		glTexParameteri(textureSides[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(textureSides[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(textureSides[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(textureSides[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	
	return true;
}

void CubemapTexture::bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObject);

}

CubemapTexture::~CubemapTexture()
{
	if(m_textureObject != 0)
		glDeleteTextures(1, &m_textureObject);
}