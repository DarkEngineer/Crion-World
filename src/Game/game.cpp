#include "Game.h"

Game * game;

Game::Game()
{
	m_pGameCamera = NULL;
	m_pEffect = NULL;
	m_scale = 1.0f;
	m_directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.ambientIntensity = 0.5f;
	m_windowWidth = 800;
	m_windowHeight = 600;
}

Game::~Game()
{
	delete m_pGameCamera;
	delete m_pEffect;
}

void Game::createWindow(int windowWidth, int windowHeight)
{
	glfwInit();
 
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow( windowWidth, windowHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
 
	glewExperimental = GL_TRUE;
	
}

bool Game::init()
{
	m_pGameCamera = new Camera(m_windowWidth, m_windowHeight);

	m_pEffect = new LightingTechnique();

	m_pGameCamera->setLastTime(static_cast<float>(glfwGetTime()));
	if(!m_pEffect->init())
		return false;

	m_pEffect->enable();

	mesh = new Mesh();
	std::string filename = "images";
	if(mesh->texturePath(filename))
		mesh->loadMesh("models/studnia.3ds");
	else
		return false;

	return true;
}

void Game::render()
{
	m_pGameCamera->checkFPS();	
	m_pGameCamera->onRender();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scale += sinf(0.1f * static_cast<float>(M_PI));

	Pipeline * p = new Pipeline();

	p->rotate(0.0f, m_scale, 0.0f);
	p->worldPos(0.0f, 0.0f, 3.0f);
	p->setCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	p->setPerspectiveProj(60.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.001f, 100.0f);
	m_pEffect->setWVP(* p->getTrans());
	m_pEffect->setDirectionalLight(m_directionalLight);
	mesh->render();
	glfwSwapBuffers();
}

void Game::onKeyboard(int key, int action)
{
	switch(key)
	{
	case 'g':
		m_directionalLight.ambientIntensity += 0.05f;
		break;
	case 'h':
		m_directionalLight.ambientIntensity -= 0.05f;
		break;
	}
}

void Game::keyboardWrapper(int key, int action)
{
	cam->onKeyboard(key, action);
	game->onKeyboard(key,action);

}