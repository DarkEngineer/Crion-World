#ifndef Landscape_h
#define Landscape_h
#include "../Texture/Texture.h"
#include "../Crion/Crion.h"

//class of heightmap which will be great for creating beautiful landscapes
class Landscape
{

	unsigned int m_width;
	unsigned int m_height;
	float m_stepSize;
	unsigned int m_numVertices;
	std::string m_name;
	std::vector <Texture> m_textures;
	GLuint m_VB;
	GLuint m_IB;
	std::vector <Crion::Vertex> m_vertices;
	std::vector <unsigned int> m_indices;
public:
	Landscape();
	~Landscape();
	bool create(std::string & landPath, unsigned int landWidth, unsigned int landHeight);
	bool create(unsigned int landWidth, unsigned int landHeight);
	virtual void render();
	void remove();

};
#endif