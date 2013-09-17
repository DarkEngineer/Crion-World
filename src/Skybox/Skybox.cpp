#include "Skybox.h"

Skybox::Skybox(const Camera * pCamera, const Pipeline & pers)
{
	m_pCamera = pCamera;
	m_projInfo = pers;

	m_pSkyboxTechnique = NULL;
	m_pMesh = NULL;
}

Skybox::~Skybox()
{
	delete m_pCamera;
	delete m_pSkyboxTechnique;
	delete m_pMesh;
}

bool Skybox::init(const std::string & directory)
{
	m_pSkyboxTechnique = new SkyboxTechnique();

	if(!m_pSkyboxTechnique->init())
	{
		std::cout << "Skybox initialization failure" << std::endl;
		return false;
	}

	m_pSkyboxTechnique->enable();
	m_pSkyboxTechnique->setTextureUnit(0);


	m_pMesh = new Mesh();
	m_pMesh->setTexturePath(const_cast<std::string &>(directory));
	return m_pMesh->loadMesh("models/skybox_cube.3ds");
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
	m_pMesh->render();

	glCullFace(faceMode);
	glDepthFunc(depthFunction);
}

