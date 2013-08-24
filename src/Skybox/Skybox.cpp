#include "Skybox.h"

Skybox::Skybox(const Camera * pCamera, const Pipeline & pers)
{
	m_pCamera = pCamera;
	m_projInfo = pers;

	m_pSkyboxTechnique = NULL;
	m_pCubemapTexture = NULL;
	m_pMesh = NULL;
}

Skybox::~Skybox()
{
	delete m_pCamera;
	delete m_pSkyboxTechnique;
	delete m_pMesh;
	delete m_pCubemapTexture;
}

bool Skybox::init(const std::string & directory,
			const std::string & posXFilename,
			const std::string & negXFilename,
			const std::string & posYFilename,
			const std::string & negYFilename,
			const std::string & posZFilename,
			const std::string & negZFilename)
{
	m_pSkyboxTechnique = new SkyboxTechnique();

	if(!m_pSkyboxTechnique->init())
	{
		std::cout << "Skybox initialization failure" << std::endl;
		return false;
	}

	m_pSkyboxTechnique->enable();
	m_pSkyboxTechnique->setTextureUnit(0);

	m_pCubemapTexture = new CubemapTexture(directory, posXFilename, negXFilename,
											posYFilename, negYFilename, posZFilename, negZFilename);

	if(!m_pCubemapTexture->load())
	{
		std::cout << "Cubemap texture loading error" << std::endl;
		return false;
	}

	m_pMesh = new Mesh();

	return m_pMesh->loadMesh("models/sphere.3ds");
}

void Skybox::render()
{
	m_pSkyboxTechnique->enable();

	GLint faceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &faceMode);
	GLint depthFunction;
	glGetIntegerv(GL_DEPTH_FUNC, &depthFunction);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	m_projInfo.scale(20.0f, 20.0f, 20.0f);
	m_projInfo.worldPos(m_pCamera->GetPos().x, m_pCamera->GetPos().y, m_pCamera->GetPos().z);
	m_projInfo.setCamera(m_pCamera->GetPos(), m_pCamera->GetTarget(), m_pCamera->GetUp());
	m_pSkyboxTechnique->setWVP(*m_projInfo.getTrans());
	m_pCubemapTexture->bind(GL_TEXTURE0);
	m_pMesh->render();

	glCullFace(faceMode);
	glDepthFunc(depthFunction);
}

