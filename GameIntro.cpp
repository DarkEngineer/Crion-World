#include "GameIntro.h"
#include "Pipeline.h"

GameIntro::GameIntro()
{
	m_pGameCamera = NULL;
	m_pTexture = NULL;
	m_pEffect = NULL;
	m_scale = 0.0f;
	m_directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.ambientIntensity = 0.5f;
}

void GameIntro::setWindow(int width, int height )
{
	window_width = width;
	window_height = height;
	glfwInit();
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow( width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

	glewExperimental = GL_TRUE;
	glewInit();
}

bool GameIntro::init()
{
	m_pGameCamera = new Camera(window_width, window_height);
	Object.loadMesh("Studnia.3ds");

	m_pEffect = new LightingTechnique();

	if(!m_pEffect->init())
		return false;

	m_pEffect->enable();

	m_pTexture = new Texture(GL_TEXTURE_2D, "test.png");

	if(!m_pTexture->Load())
		return false;

	return true;
}
Game * GameIntro::nextGameState()
{
	return this;
}


void GameIntro::render()
{
	int x, y;
	glfwGetMousePos(&x, &y);
	m_pGameCamera->onMouse(x, y);
	m_pGameCamera->onRender();
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_scale += 0.1f;

	Pipeline p;
	p.rotate(0.0f, m_scale, 0.0f);
	p.worldPos(0.0f, 0.0f, 3.0f);
	p.setCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	p.setPerspectiveProj(60.0f,static_cast<float>(window_width), static_cast<float>(window_height), 1.0f, 100.0f);
	m_pEffect->setWVP(p.getWVPTrans());
	m_pEffect->setDirectionalLight(m_directionalLight);

	Object.render();
}

void GameIntro::Update()
{
}

GameIntro::~GameIntro()
{
	delete m_pEffect;
	delete m_pGameCamera;
	delete m_pTexture;
}
