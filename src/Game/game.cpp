#include "Game.h"

Game * game;

Game::Game()
{
	mesh = new Mesh();
	m_scale = 1.0f;
	m_directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.ambientIntensity = 0.5f;
    m_directionalLight.diffuseIntensity = 0.75f;
    m_directionalLight.direction = glm::vec3(1.0f, -1.0, 0.0);
	m_windowWidth = 800;
	m_windowHeight = 600;
}

Game::~Game()
{
	delete pipe;
	delete m_pEffect;
	delete mesh;
	delete pointLight;
	delete & m_scale;
	delete & m_directionalLight;
	delete & m_windowWidth;
	delete & m_windowHeight;
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
	pipe = new Pipeline();
	pipe->setCamera(m_windowWidth, m_windowHeight);
	pipe->init();
	gameCamera = pipe->getCamera();
	m_pEffect = new LightingTechnique();

	if(!m_pEffect->init())
		return false;

	m_pEffect->enable();
	std::string filename = "images";
	if(mesh->setTexturePath(filename))
		mesh->loadMesh("models/studnia.3ds");
	else
		return false;


	cam = gameCamera;
	glfwSetMouseButtonCallback(Game::mouseButtonWrapper);
	glfwSetCharCallback(Game::keyboardWrapper);
	glfwSetMousePosCallback(Game::mousePosWrapper);
	glfwSetKeyCallback(Game::keyboardWrapper);

	return true;
}

void Game::render()
{
	m_scale += 0.0057f;
	pipe->render();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PointLight pointLight[2];
	pointLight[0].diffuseIntensity = 0.5f;
	pointLight[0].color = glm::vec3(1.0f, 0.5f, 0.0f);
	pointLight[0].position = glm::vec3(0.0f, 2.0f, 0.0f);
	pointLight[0].attentuation.linear = 0.1f;
	pointLight[1].diffuseIntensity = 0.5f;
	pointLight[1].color = glm::vec3(0.0f, 0.5f, 1.0f);
	pointLight[1].position = glm::vec3(2.0f, 2.0f, 0.0f);
	pointLight[1].attentuation.linear = 0.1f;
	m_pEffect->setPointLights(2, pointLight);
	pipe->setCamera(gameCamera->GetPos(), gameCamera->GetTarget(), gameCamera->GetUp());
	pipe->setPerspectiveProj(75.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.001f, 100.0f);
	m_pEffect->setWorldMatrix(* pipe->getWorldTrans());
	m_pEffect->setWVP(* pipe->getTrans());
	m_pEffect->setDirectionalLight(m_directionalLight);
	m_pEffect->setEyeWorldPos(gameCamera->GetPos());
	m_pEffect->setSpecularIntensity(1.0f);
	m_pEffect->setSpecularPower(32);
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
	case 'a':
		m_directionalLight.ambientIntensity += 0.05f;
		break;
	case 's':
		m_directionalLight.ambientIntensity -= 0.05f;
		break;
	case 'z':
		m_directionalLight.diffuseIntensity += 0.05f;
		break;
	case 'x':
		m_directionalLight.diffuseIntensity -= 0.05f;
		break;
	}

	if(m_directionalLight.ambientIntensity < 0.0f)
		m_directionalLight.ambientIntensity = 0.0f;
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
	cam->onMousePos(x, y);
}