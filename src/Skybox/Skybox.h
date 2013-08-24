#ifndef Skybox_h
#define Skybox_h
#include "SkyboxTechnique/SkyboxTechnique.h"
#include "CubemapTexture/CubemapTexture.h"
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"

class Skybox
{
	SkyboxTechnique * m_pSkyboxTechnique;
	CubemapTexture * m_pCubemapTexture;
	const Camera * m_pCamera;
	Mesh * m_pMesh;
	Pipeline m_projInfo;

public:
	Skybox(const Camera * pCamera, const Pipeline & pers);

	~Skybox();

	bool init(const std::string & directory,
				const std::string & posXFilename,
				const std::string & negXFilename,
				const std::string & posYFilename,
				const std::string & negYFilename,
				const std::string & posZFilename,
				const std::string & negZFilename);

	void render();
};

#endif