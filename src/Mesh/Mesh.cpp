#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
  clear();
  delete & m_Entries;
  delete & m_Textures;
  delete & m_texturePath;
}

void Mesh::clear()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		delete m_Textures[i];
	
}

Mesh::MeshEntry::MeshEntry()
{
	VB = GL_INVALID_ENUM;
	IB = GL_INVALID_ENUM;
	numIndices = 0;
	materialIndex = INVALID_MATERIAL;
}

Mesh::MeshEntry::~MeshEntry()
{
	if(VB != GL_INVALID_ENUM)
		glDeleteBuffers(1, &VB);
	if(IB != GL_INVALID_ENUM)
		glDeleteBuffers(1, &IB);
}

void Mesh::MeshEntry::init(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices)
{
	numIndices = indices.size();
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
}
bool Mesh::loadMesh(const std::string & filename)
{
	clear();
	
	bool Ret = false;
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename.c_str(), aiProcessPreset_TargetRealtime_Quality);

	if(pScene)
		Ret = initFromScene(pScene, filename);
	else
		std::cout << "Error passing " << filename << " : " << importer.GetErrorString() << std::endl;

	return Ret;
}

// reading path of file where textures are contained in string
bool Mesh::setTexturePath(std::string &filename)
{
	std::string undef = "";
	m_texturePath = filename;
	if(!(m_texturePath == filename && m_texturePath != undef) )
		return false;

	return true;
}

// reading path in chars
bool Mesh::setTexturePath(const char* & filename)
{
	std::string undef = "";
	m_texturePath = filename;
	if(!(m_texturePath == filename && m_texturePath != undef))
		return false;

	return true;
}

std::string * Mesh::getTexturePath()
{
	return & m_texturePath;
}
bool Mesh::initFromScene(const aiScene* pScene, const std::string &filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	for(unsigned int i = 0; i < m_Entries.size(); i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		initMesh(i, paiMesh);
	}

	return initMaterials(pScene, filename);
}

void Mesh::initMesh(unsigned int index, const aiMesh* paiMesh)
{
	m_Entries[index].materialIndex = paiMesh->mMaterialIndex;

	std::vector <Vertex> vertices;
	std::vector <unsigned int> indices;

	const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

	for(unsigned int i = 0; i < paiMesh->mNumVertices; i++)
	{
		const aiVector3D * pPos = &(paiMesh->mVertices[i]);
		const aiVector3D *pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D *pTextCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero3D;

		Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z), glm::vec2(pTextCoord->x, pTextCoord->y), glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		vertices.push_back(v);
	}

	for(unsigned int i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace &face = paiMesh->mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	m_Entries[index].init(vertices, indices);
}

bool Mesh::initMaterials(const aiScene* pScene, const std::string &filename)
{
	std::string::size_type SlashIndex = filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = filename.substr(0, SlashIndex);
    }

    bool Ret = true;

	for(unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{
		const aiMaterial *pMaterial = pScene->mMaterials[i];
		m_Textures[i] = NULL;
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
		{
            aiString path;
			std::string slash = "/";

			if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string fullPath;
				if(&m_texturePath != NULL)
				{
					fullPath = m_texturePath + slash + path.data;
				}
				else
				{
					fullPath = path.data;
				}
				m_Textures[i] = new Texture(GL_TEXTURE_2D, fullPath.c_str());

				if(!m_Textures[i]->Load())
				{
					std::cout << "Error Loading texture " << fullPath.c_str() << std::endl;
					delete m_Textures[i];
					m_Textures[i] = NULL;
					Ret = false;

				}
			}
		}

		if(!m_Textures[i])
		{
			m_Textures[i] = new Texture(GL_TEXTURE_2D, "images/chessboard.jpg");
			Ret = m_Textures[i]->Load();
		}
	}

	return Ret;
}

void Mesh::render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for(unsigned int i = 0; i < m_Entries.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

		const unsigned int materialIndex = m_Entries[i].materialIndex;

		if( materialIndex < m_Textures.size() && m_Textures[materialIndex])
		{
			m_Textures[materialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElements(GL_TRIANGLES, m_Entries[i].numIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

