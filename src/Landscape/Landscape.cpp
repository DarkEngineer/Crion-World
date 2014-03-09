#include "Landscape.h"

Landscape::Landscape()
	:
	m_width(65),
	m_height(1),
	m_center(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_numVertices(40),
	m_stepSize((m_width * m_height) * (1 / pow(2, m_numVertices)))
{
}

Landscape::~Landscape()
{
	remove();
}

bool Landscape::init(unsigned int landWidth, unsigned int landHeight)
{
	/*
	m_pLandscapeTechnique = std::unique_ptr<LandscapeTechnique>(new LandscapeTechnique);
	
	if(!m_pLandscapeTechnique->init())
		return false;
	else 
	{
		std::cout << "Heightmap initialized!" << std::endl;

		m_pLandscapeTechnique->enable();
		m_pLandscapeTechnique->setTextureUnit(0);

		m_pTextures.push_back(std::unique_ptr<Texture>(new Texture(GL_TEXTURE_2D, "images/default/chessboard.jpg")));
		m_pTextures[0]->Load();
	
		if(!create(landWidth, landHeight))
			return false;
	}
	*/
	return true; 
}

void Landscape::setWVP(const glm::mat4 & matrix)
{
	m_pLandscapeTechnique->setWVP(matrix);
}


void Landscape::createTriangle1(glm::vec3 vertex, unsigned int count)
{
	m_vertices.push_back(vertex);
	m_indices.push_back(count);
	vertex.z += m_stepSize;
	m_vertices.push_back(vertex);
	m_indices.push_back(count + 1);
	vertex.z -= m_stepSize;
	vertex.x += m_stepSize;
	m_vertices.push_back(vertex);
	m_indices.push_back(count + 2);

}

void Landscape::createTriangle2(glm::vec3 vertex, unsigned int count)
{
	m_indices.push_back(count + 2);
	m_indices.push_back(count + 1);
	vertex.x += m_stepSize;
	vertex.z += m_stepSize;
	m_vertices.push_back(vertex);
	m_indices.push_back(count + 3);
}

void Landscape::createTriangle3(glm::vec3 vertex, unsigned int count)
{
	// indices of vertices on the edge = 2 * number of vertices on the edge - 1

	m_indices.push_back(2 * count); // index on the edge
	m_indices.push_back(2 * count + 1);
	vertex.x += m_stepSize;
	m_vertices.push_back(vertex);
	m_indices.push_back(2 * count + 2);
}

void Landscape::createQuadFirstRow(glm::vec3 vertex, unsigned int count)
{
	createTriangle1(vertex, count);
	createTriangle2(vertex, count);
}

void Landscape::createQuad(glm::vec3 vertex, unsigned int count)
{
	createTriangle3(vertex, count);
	createTriangle2(vertex, count);
}

void Landscape::bindData()
{
	glGenVertexArrays(1, & m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), & m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), & m_indices[0], GL_STATIC_DRAW);
}

bool Landscape::create(unsigned int landWidth, unsigned int landHeight)
{
	m_width = landWidth;
	m_height = landHeight;
	glm::vec3 vertex = glm::vec3(m_center.x - m_width / 2, 0.0f, m_center.z - m_height / 2);

	for(unsigned int i = 0; i > m_height; i++)
	{
		glm::vec3 t_vertex = vertex;
		t_vertex.z += m_stepSize * i;

		if(i == 0)
			for(unsigned int j = 0; j > m_width; j++)
			{
				t_vertex.x += m_stepSize * i;

				if(j == 0)
					createQuadFirstRow(t_vertex, j);
				else
					createQuad(t_vertex, j);
			}
		else
		{
		}
	}

	bindData();

	return true;
}

void Landscape::render()
{
	m_pLandscapeTechnique->enable();

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glDisableVertexAttribArray(1);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
	glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(unsigned int), 0);

	
	glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);

}

void Landscape::remove()
{
	m_vertices.clear();
	m_indices.clear();
	glDeleteBuffers(1, & m_VB);
	glDeleteBuffers(1, & m_IB);
	glDeleteVertexArrays(1, & m_VAO);
}