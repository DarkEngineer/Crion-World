#ifndef Skybox_h
#define Skybox_h
#include "SkyboxTechnique/SkyboxTechnique.h"
#include "CubemapTexture/CubemapTexture.h"
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"

class Skybox
{
	SkyboxTechnique * m_pSkyboxTechnique;
	const Camera * m_pCamera;
	Mesh * m_pMesh;
	Pipeline m_projInfo;

public:
	Skybox(const Camera * pCamera, const Pipeline & pers);

	~Skybox();

	bool Skybox::init(const std::string & directory);
	void render();
};

#endif