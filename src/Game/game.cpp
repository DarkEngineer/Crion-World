#include "Game.h"

Game * game;

Game::Game()
{
	pipe = NULL;
	m_pEffect = NULL;
	mesh = new Mesh();
	m_scale = 1.0f;
	m_directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.ambientIntensity = 0.5f;
	m_windowWidth = 800;
	m_windowHeight = 600;
}

Game::~Game()
{
	delete pipe;
	delete m_pEffect;
	delete mesh;
}

void Game::createWindow(int windowWidth, int windowHeight)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
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
	Pipeline * pipe = new Pipeline();
	pipe->setCamera(m_windowWidth, m_windowHeight);
	pipe->init();
	m_pEffect = new LightingTechnique();

	if(!m_pEffect->init())
		return false;

	m_pEffect->enable();
	std::string filename = "images";
	if(mesh->setTexturePath(filename))
		mesh->loadMesh("models/studnia.3ds");
	else
		return false;
	std::cout << "Texture: " << * getMesh()->getTexturePath() << std::endl;

	return true;
}

void Game::render()
{
	pipe->render();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scale += sinf(0.1f * static_cast<float>(M_PI));

	pipe->rotate(0.0f, m_scale, 0.0f);
	pipe->worldPos(0.0f, 0.0f, 3.0f);
	pipe->setPerspectiveProj(60.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.001f, 100.0f);
	pipe->setCamera(pipe->getCamera()->GetPos(), pipe->getCamera()->GetTarget(), pipe->getCamera()->GetUp());
	m_pEffect->setWVP(* pipe->getTrans());
	m_pEffect->setDirectionalLight(m_directionalLight);
	mesh->render();
	glfwSwapBuffers();
}

Mesh * Game::getMesh()
{
	return mesh;
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
	game->onKeyboard(key, action);

}

void Game::mouseButtonWrapper(int button, int action)
{
	cam->onMouseButton(button, action);
}

void Game::mousePosWrapper(int x, int y)
{
	Camera * camera = pipeline->getCamera();
	camera->onMousePos(x, y);
 }