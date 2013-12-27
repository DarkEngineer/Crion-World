#ifndef Landscape_h
#define Landscape_h
#include "../Texture/Texture.h"
#include "LandscapeTechnique.h"
#include <memory>

//class of heightmap which will be great for creating beautiful landscapes
class Landscape
{
	std::unique_ptr <LandscapeTechnique> m_pLandscapeTechnique;
	unsigned int m_width;
	unsigned int m_height;
	glm::vec3 m_center;
	float m_stepSize;
	unsigned int m_numVertices;
	std::string m_name;
	std::vector <std::unique_ptr<Texture>> m_pTextures;
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
 
	bool create(std::string & landPath, unsigned int landWidth, unsigned int landHeight);
	bool create(unsigned int landWidth, unsigned int landHeight);

	void bindData();
public:
	Landscape();
	~Landscape();
	// method for creating map with (landWidth x landHeight) size
	bool init(unsigned int landWidth, unsigned int landHeight);
	void setWVP(const glm::mat4 & matrix);
	void loadTexture(std::string name);
	virtual void render();
	void remove();

};
#endif