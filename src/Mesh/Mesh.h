#ifndef Mesh_h
#define Mesh_h

#include "../Texture/Texture.h"
#include <map>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

struct Vertex
{
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_normal;

    Vertex() {}

    Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};

class Mesh
{
  bool initFromScene(const aiScene* pScene, const std::string &Filename);
	void initMesh(unsigned int index, const aiMesh* paiMesh);
	bool initMaterials(const aiScene* pScene, const std::string &Filename);
	void clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct MeshEntry
	{
		MeshEntry();

		virtual ~MeshEntry();

		void init(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);

		GLuint VB;
		GLuint IB;
		unsigned int numIndices;
		unsigned int materialIndex;
	};

	std::vector <MeshEntry> m_Entries;
	std::vector <Texture*> m_Textures;
	const std::string * m_texturePath;

public:
	Mesh();

	virtual ~Mesh();
	
	bool loadMesh(const std::string &filename);
	bool texturePath(const std::string &filename);

	void render();
};
#endif
