#include "stdafx.h"
#include "CppUnitTest.h"
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <GL\glew.h>
#include <GL\GL.h>
#include <glm\glm.hpp>
#include <texture.h>
#include <glFreeImage.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestingProject
{
	BEGIN_TEST_MODULE_ATTRIBUTE()
		TEST_MODULE_ATTRIBUTE(L"DATE", L"2013/03/21")
		END_TEST_MODULE_ATTRIBUTE()

	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

#define INVALID_MATERIAL 0xFFFFFFFF	
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

	struct MeshEntry
	{
	MeshEntry()
	{
		VB = GL_INVALID_ENUM;
		IB = GL_INVALID_ENUM;
		numIndices = 0;
		materialIndex = INVALID_MATERIAL;
	}

	~MeshEntry()
	{
		if(VB != GL_INVALID_ENUM)
			glDeleteBuffers(1, &VB);
		if(IB != GL_INVALID_ENUM)
			glDeleteBuffers(1, &IB);
	}

		void init(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);

		GLuint VB;
		GLuint IB;
		unsigned int numIndices;
		unsigned int materialIndex;
	};

	TEST_CLASS(Mesh)
	{
		std::vector <MeshEntry> m_Entries;

	void loadMesh(std::string filename);

	
	BEGIN_TEST_METHOD_ATTRIBUTE(loadMesh)
		TEST_OWNER(L"loadMesh")
		TEST_METHOD_ATTRIBUTE(L"filename", L"Studnia.3ds")
		TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(loadMesh)
	{
		std::string filename = "Studnia.3ds";
		
	
		bool Ret = false;
		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile( filename, aiProcessPreset_TargetRealtime_Quality);

		Assert::IsNotNull(pScene);

		m_Entries.resize(pScene->mNumMeshes);
		Assert::AreNotSame(0, static_cast<int>(pScene->mNumMaterials));
		
		std::string done = "Correct :" + pScene->mNumMaterials;
		if(pScene->mNumMaterials != 0)
			Logger::WriteMessage(done.c_str());
		

	}


};

}