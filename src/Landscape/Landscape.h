#ifndef Landscape_h
#define Landscape_h
#include "../Texture/Texture.h"

//class of heightmap which will be great for creating beautiful landscapes
class Landscape
{

	unsigned int m_width;
	unsigned int m_height;
	glm::vec3 m_center;
	float m_stepSize;
	unsigned int m_numVertices;
	std::string m_name;
	std::vector <Texture> m_textures;
	GLuint m_VAO;
	GLuint m_VB;
	GLuint m_IB;
	std::vector <glm::vec3> m_vertices;
	std::vector <unsigned int> m_indices;

	//first triangle which is part of quad
	void createTriangle1(glm::vec3 vertex, unsigned int count); 
	//second triangle which is part of quad
	void createTriangle2(glm::vec3 vertex, unsigned int count);
	//triangle where it has created two vertices on the left side from quad made before
	void createTriangle3(glm::vec3 vertex, unsigned int count);
	// quad = 2 triangles
	void createQuadFirstRow(glm::vec3 vertex, unsigned int count);
	// quad which doesn't contain first vertex of heightmap
	void createQuad(glm::vec3 vertex, unsigned int count);

	void bindData();
public:
	Landscape();
	~Landscape();
	bool create(std::string & landPath, unsigned int landWidth, unsigned int landHeight);
	bool create(unsigned int landWidth, unsigned int landHeight);
	virtual void render();
	void remove();

};
#endif