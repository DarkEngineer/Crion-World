#include "Game.h"

Game * game;

Game::Game()
{
	mesh = new Mesh();
	m_scale = 1.0f;
	m_directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.ambientIntensity = 0.5f;
    m_directionalLight.diffuseIntensity = 0.75f;
    m_directionalLight.direction = glm::vec3(0.0, -1.0, 0.0);
	m_windowWidth = 800;
	m_windowHeight = 600;
	spotLight = new SpotLight[2];
	spotLight->ambientIntensity = 0.1f;
    spotLight->diffuseIntensity = 0.9f;
    spotLight->color = glm::vec3(1.0f, 1.0f, 1.0f);
    spotLight->attentuation.linear = 0.01f;
    spotLight->position  = glm::vec3(0.0f, 40.0f, 1.0f);
    spotLight->direction = glm::vec3(0.0f, -1.0f, 0.0f);
    spotLight->cutoff =  20.0f;
	m_pShadowMapEffect = new ShadowMapTechnique();

}

Game::~Game()
{
	delete pipe;
	delete m_pLightingEffect;
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
	m_shadowMap = new ShadowMap();

	if(!m_shadowMap->initShadow(m_windowWidth, m_windowHeight))
		return false;

	m_pLightingEffect = new LightingTechnique();
	if(!m_pLightingEffect->init())
		return false;

	m_pLightingEffect->enable();
	m_pLightingEffect->setSpotLights(1, spotLight);
	m_pLightingEffect->setTextureUnit(0);
	m_pLightingEffect->setShadowMapTextureUnit(1);

	m_pShadowMapEffect = new ShadowMapTechnique();
	if(!m_pShadowMapEffect->init())
		return false;


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

void Game::shadowMapPass()
{
	m_shadowMap->bindForWriting();

	glClear(GL_DEPTH_BUFFER_BIT);

	m_pShadowMapEffect->enable();
	
	pipe->scale(1.0f, 1.0f, 1.0f);
	pipe->rotate(0.0f, 0.0f, 0.0f);
	pipe->setCamera(spotLight->position, spotLight->direction, glm::vec3(0.0f, 1.0f, 0.0));
	pipe->setPerspectiveProj(75.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.001f, 100.0f);
	m_pShadowMapEffect->setMatrix(* pipe->getTrans());
	mesh->render();

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
}

void Game::renderPass()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pLightingEffect->enable();
	renderPointLights();
	renderSpotLights();
	pipe->scale(1.0f, 1.0f, 1.0f);
	pipe->rotate(0.0f, 0.0f, 0.0f);
	pipe->setPerspectiveProj(75.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.001f, 100.0f);
	pipe->setCamera(gameCamera->GetPos(), gameCamera->GetTarget(), gameCamera->GetUp());
	m_pLightingEffect->setWVP(* pipe->getTrans());
	m_pLightingEffect->setWorldMatrix(* pipe->getWorldTrans());
	m_pLightingEffect->setNormalMatrix(glm::transpose(glm::inverse(glm::mat3((*pipe->getWorldTrans())))));
	m_pLightingEffect->setEyeWorldPos(gameCamera->GetPos());
	m_pLightingEffect->setSpecularIntensity(1.0f);
	m_pLightingEffect->setSpecularPower(32);
	pipe->setCamera(spotLight->position, spotLight->direction, glm::vec3(0.0f, 1.0f, 0.0));
	m_pLightingEffect->setLightMatrix(* pipe->getTrans());
	mesh->render();
}

void Game::render()
{
	m_scale += 0.0057f;
	pipe->render();

	shadowMapPass();
	renderPass();

	glfwSwapBuffers();
}
void Game::renderPointLights()
{
	PointLight pointLight[2];
	pointLight[0].diffuseIntensity = 1.0f;
	pointLight[0].color = glm::vec3(0.25f, 0.5f, 0.0f);
	pointLight[0].position = glm::vec3(6.0f * ((cosf(m_scale) + 3.0f) / 2.0f), 2.0f, (cosf(m_scale) + 1.0f) / 2.0f);
	pointLight[0].attentuation.linear = 0.1f;
	pointLight[1].diffuseIntensity = 1.0f;
	pointLight[1].color = glm::vec3(0.0f, 0.5f, 0.25f);
	pointLight[1].position = glm::vec3(2.0f, 7.0f, (sinf(m_scale) + 1.0f) / 2.0f);
	pointLight[1].attentuation.linear = 0.1f;
	m_pLightingEffect->setPointLights(2, pointLight);

}

void Game::renderSpotLights()
{
	//SpotLight spotLight[2];
	//spotLight[0].diffuseIntensity = 0.9f;
	//spotLight[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	//spotLight[0].position = gameCamera->GetPos();
	//spotLight[0].direction = gameCamera->GetTarget();
	//spotLight[0].attentuation.linear = 0.5f;
	//spotLight[0].cutoff = 5.0f;
	//spotLight[1].diffuseIntensity = 1.0f;
	//spotLight[1].color = glm::vec3(0.5f, 1.0f, 0.5f);
	//spotLight[1].position = glm::vec3(6.0f, 5.0f, 2.0f);
	//spotLight[1].direction = glm::vec3(0.0f, -1.0f, 0.0f);
	//spotLight[1].attentuation.exp = 0.6f;
	//spotLight[1].cutoff = 5.0f;
	m_pLightingEffect->setSpotLights(1, spotLight);

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