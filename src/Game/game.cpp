#include "Game.h"

Game * game;

Game::Game()
	:
	m_scale(1.0f),
	m_windowWidth(800),
	m_windowHeight(600),
	m_pObjects(new Object_manager()),
	m_pSkybox(NULL)
{
	initDirectionaLights();
	initSpotLights();

}

bool Game::init()
{
	m_pPipe = new Pipeline();
	m_pPipe->setCamera(m_windowWidth, m_windowHeight);
	m_pPipe->init();
	m_pGameCamera = m_pPipe->getCamera();
	m_pShadowMap = new ShadowMap();

	if(!m_pShadowMap->initShadow(m_windowWidth, m_windowHeight))
		return false;

	m_pLightingEffect = new LightingTechnique();
	if(!m_pLightingEffect->init())
		return false;

	m_pLightingEffect->enable();
	m_pLightingEffect->setSpotLights(1, m_pSpotLight);
	m_pLightingEffect->setTextureUnit(0);
	m_pLightingEffect->setShadowMapTextureUnit(1);

	m_pShadowMapEffect = new ShadowMapTechnique();
	if(!m_pShadowMapEffect->init())
		return false;

	if(!initModels())
		std::cout << "LOG: Models error" << std::endl;

	if(!initSkybox())
		std::cout << "LOG: Skybox initialization error!" << std::endl;

	cam = m_pGameCamera;
	glfwSetMouseButtonCallback(m_pWindow, Game::mouseButtonWrapper);
	glfwSetCharCallback(m_pWindow, Game::keyboardCharactersWrapper);
	glfwSetCursorPosCallback(m_pWindow, Game::mousePosWrapper);
	glfwSetKeyCallback(m_pWindow, Game::keyboardWrapper);

	return true;
}

void Game::initDirectionaLights()
{
	m_pDirectionalLight = new DirectionalLight();
	m_pDirectionalLight->color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_pDirectionalLight->ambientIntensity = 0.5f;
    m_pDirectionalLight->diffuseIntensity = 0.75f;
    m_pDirectionalLight->direction = glm::vec3(0.0, -1.0, 0.0);

}

void Game::initPointLights()
{
}

void Game::initSpotLights()
{
		m_pSpotLight = new SpotLight[2];
	m_pSpotLight[0].ambientIntensity = 0.1f;
    m_pSpotLight[0].diffuseIntensity = 0.9f;
    m_pSpotLight[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_pSpotLight[0].attentuation.linear = 0.01f;
    m_pSpotLight[0].position  = glm::vec3(0.0f, 40.0f, 1.0f);
    m_pSpotLight[0].direction = glm::vec3(0.0f, -1.0f, 0.0f);
    m_pSpotLight[0].cutoff =  20.0f;

}

bool Game::initModels()
{
	bool value = false;
		if(m_pObjects->addObject(glm::vec3(0, 6, 0), "models/human_body.3ds", "images") )
		{
			std::cout << "Object" << " created" << std::endl;
			value = true;

		}
		else
		{
			std::cout << "Object creation failed" << std::endl;
			value = false;
		}
	
	if(m_pObjects->addObject(glm::vec3(0, -3, 0), "models/studnia.3ds", "images"))
	{
		std::cout << "Object" << " created" << std::endl;
		value = true;

	}
	else
	{
		std::cout << "Object creation failed" << std::endl;
		value = false;
	}

	for(std::vector<std::unique_ptr<Object>>::iterator iter = m_pObjects->getObjects().begin();  iter != m_pObjects->getObjects().end(); iter++)
	{
		std::cout << "Object coords: x:" << (* iter)->getPosition().x << " y:" << (*iter)->getPosition().y << " z:" << (*iter)->getPosition().z << std::endl;
	}
	return value;
}

bool Game::initSkybox()
{
	m_pSkybox = new Skybox(m_pGameCamera, * m_pPipe);

	if(!m_pSkybox->init("images/skybox_tex"))
		return false;
	else
		std::cout << "Skybox created!" << std::endl;

	return true;
}

void Game::createWindow(int windowWidth, int windowHeight)
{
	glfwSetErrorCallback(Game::errorCallback);
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
    m_pWindow = glfwCreateWindow(windowWidth, windowHeight, "Crion World", NULL, NULL);
	if(!m_pWindow)
		exit(EXIT_FAILURE);
	glfwMakeContextCurrent(m_pWindow);
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	*/
	glewExperimental = GL_TRUE;
	
}

void Game::destroyWindow()
{
	glfwDestroyWindow(m_pWindow);
}

void Game::shadowMapPass()
{
	m_pShadowMap->bindForWriting();

	glClear(GL_DEPTH_BUFFER_BIT);

	m_pShadowMapEffect->enable();
	
	m_pPipe->scale(1.0f, 1.0f, 1.0f);
	m_pPipe->rotate(0.0f, 0.0f, 0.0f);
	m_pPipe->setCamera(m_pSpotLight->position, m_pSpotLight->direction, glm::vec3(0.0f, 1.0f, 0.0));
	m_pPipe->setPerspectiveProj(75.0f, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight), 0.001f, 10000.0f);
	m_pShadowMapEffect->setMatrix(* m_pPipe->getTrans());
	m_pObjects->render(m_pPipe, * m_pLightingEffect);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
}

void Game::renderPass()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pLightingEffect->enable();
	renderPointLights();
	renderSpotLights();
	renderLightEffects();
	m_pPipe->setCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	m_pObjects->render(m_pPipe, * m_pLightingEffect);

	renderSkybox();
}

void Game::render()
{
	m_pPipe->render();

	shadowMapPass();
	renderPass();

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
} 

void Game::renderPointLights()
{
	PointLight m_pPointLight[2];
	m_pPointLight[0].diffuseIntensity = 1.0f;
	m_pPointLight[0].color = glm::vec3(0.25f, 0.5f, 0.0f);
	m_pPointLight[0].position = glm::vec3(6.0f * ((cosf(m_scale) + 3.0f) / 2.0f), 2.0f, (cosf(m_scale) + 1.0f) / 2.0f);
	m_pPointLight[0].attentuation.linear = 0.1f;
	m_pPointLight[1].diffuseIntensity = 1.0f;
	m_pPointLight[1].color = glm::vec3(0.0f, 0.5f, 0.25f);
	m_pPointLight[1].position = glm::vec3(2.0f, 7.0f, (sinf(m_scale) + 1.0f) / 2.0f);
	m_pPointLight[1].attentuation.linear = 0.1f;
	m_pLightingEffect->setPointLights(2, m_pPointLight);

}

void Game::renderSpotLights()
{
	m_pSpotLight->diffuseIntensity = 0.9f;
	m_pSpotLight->color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_pSpotLight->position = m_pGameCamera->GetPos();
	m_pSpotLight->direction = m_pGameCamera->GetTarget();
	m_pSpotLight->attentuation.linear = 0.5f;
	m_pSpotLight->cutoff = 5.0f;
	m_pLightingEffect->setSpotLights(1, m_pSpotLight);

}

void Game::renderLightEffects()
{
	m_pLightingEffect->setWVP(* m_pPipe->getTrans());
	m_pLightingEffect->setWorldMatrix(* m_pPipe->getWorldTrans());
	m_pLightingEffect->setNormalMatrix(glm::transpose(glm::inverse(glm::mat3((*m_pPipe->getWorldTrans())))));
	m_pLightingEffect->setEyeWorldPos(m_pGameCamera->GetPos());
	m_pLightingEffect->setSpecularIntensity(1.0f);
	m_pLightingEffect->setSpecularPower(32);
	m_pLightingEffect->setDirectionalLight(*m_pDirectionalLight);
	m_pPipe->setCamera(m_pSpotLight->position, m_pSpotLight->direction, glm::vec3(0.0f, 1.0f, 0.0));
	m_pLightingEffect->setLightMatrix(* m_pPipe->getTrans());
	

}

void Game::renderSkybox()
{
	m_pSkybox->render();
}

Object_manager * Game::getObjects()
{
	return m_pObjects;
}

GLFWwindow * Game::getWindow()
{
	return m_pWindow;
}

void Game::onKeyboard(GLFWwindow * m_pWindow, int key, int action)
{

	if(glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_pWindow, GL_TRUE);

}

void Game::onKeyboardCharacters(GLFWwindow * m_pWindow, unsigned int character)
{
		switch(character)
		{
		case GLFW_KEY_A:
			m_pDirectionalLight->ambientIntensity += 0.05f;
			break;
		case GLFW_KEY_S:
			m_pDirectionalLight->ambientIntensity -= 0.05f;
			break;
		case GLFW_KEY_Z:
			m_pDirectionalLight->diffuseIntensity += 0.05f;
			break;
		case GLFW_KEY_X:
			m_pDirectionalLight->diffuseIntensity -= 0.05f;
			break;
		}

	//if(m_pDirectionalLight->ambientIntensity < 0.0f)
	//	m_pDirectionalLight->ambientIntensity = 0.0f;

}

void Game::errorCallback(int error, const char* description)
{
	std::cout << error << " " << description << std::endl;
}

void Game::keyboardWrapper(GLFWwindow* m_pWindow, int key, int scancode, int action, int mods)
{
	cam->onKeyboard(m_pWindow, key, action);
	game->onKeyboard(m_pWindow, key, action);

}

void Game::keyboardCharactersWrapper(GLFWwindow * m_pWindow, unsigned int character)
{
	game->onKeyboardCharacters(m_pWindow, character);
	cam->onKeyboardCharacters(m_pWindow, character);
}

void Game::mouseButtonWrapper(GLFWwindow * m_pWindow, int button, int action, int mods)
{
	cam->onMouseButton(m_pWindow, button, action);
}

void Game::mousePosWrapper(GLFWwindow * m_pWindow, double x, double y)
{
	cam->onMousePos(m_pWindow, static_cast<int>(x), static_cast<int>(y));
}

Game::~Game()
{
	delete m_pShadowMapEffect;
	delete m_pGameCamera;
	delete m_pPipe;
	delete m_pLightingEffect;
	delete m_pPointLight;
	delete m_pDirectionalLight;
}
