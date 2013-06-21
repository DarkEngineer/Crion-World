#ifndef Texture_h
#define Texture_h

#include "../shader/Shader.h"

// class for creating texture opengl textures
class Texture
{
	std::string m_filename;
	GLuint t_Texture;
	GLenum m_textureTarget;
	public:
		Texture();
		Texture(GLenum textureTarget, const std::string & filename);
		bool Load(); // loading texture
		bool LoadMipMaps( const std::string & s_Filename ); // loading texture with mipmaps
		void Bind(GLenum textureUnit) const;
		virtual ~Texture();
};

#endif