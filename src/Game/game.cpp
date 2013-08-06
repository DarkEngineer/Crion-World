#include "Game.h"

Game * game;

Game::Game()
	:
	m_scale(1.0f),
	m_windowWidth(800),
	m_windowHeight(600)
{
	initDirectionaLights();
	initSpotLights();
	m_pShadowMapEffect = new ShadowMapTechnique();
	m_objects = new Object_manager();

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

	if(!initModels())
		std::cout << "LOG: Models error" << std::endl;

	cam = gameCamera;
	glfwSetMouseButtonCallback(window, Game::mouseButtonWrapper);
	glfwSetCharCallback(window, Game::keyboardCharactersWrapper);
	glfwSetCursorPosCallback(window, Game::mousePosWrapper);
	glfwSetKeyCallback(window, Game::keyboardWrapper);

	return true;
}

void Game::initDirectionaLights()
{
	m_directionalLight = new DirectionalLight();
	m_directionalLight->color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight->ambientIntensity = 0.5f;
    m_directionalLight->diffuseIntensity = 0.75f;
    m_directionalLight->direction = glm::vec3(0.0, -1.0, 0.0);

}

void Game::initPointLights()
{
}

void Game::initSpotLights()
{
		spotLight = new SpotLight[2];
	spotLight[0].ambientIntensity = 0.1f;
    spotLight[0].diffuseIntensity = 0.9f;
    spotLight[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
    spotLight[0].attentuation.linear = 0.01f;
    spotLight[0].position  = glm::vec3(0.0f, 40.0f, 1.0f);
    spotLight[0].direction = glm::vec3(0.0f, -1.0f, 0.0f);
    spotLight[0].cutoff =  20.0f;

}

bool Game::initModels()
{
	bool value = false;
		if(m_objects->addObject(glm::vec3(0, 6, 0), "models/human_body.3ds", "images") )
		{
			std::cout << "Object" << " created" << std::endl;
			value = true;

		}
		else
		{
			std::cout << "Object creation failed" << std::endl;
			value = false;
		}
	
	if(m_objects->addObject(glm::vec3(0, -3, 0), "models/studnia.3ds", "images"))
	{
		std::cout << "Object" << " created" << std::endl;
		value = true;

	}
	else
	{
		std::cout << "Object creation failed" << std::endl;
		value = false;
	}

	for(std::vector<std::unique_ptr<Object>>::iterator iter = m_objects->getObjects().begin();  iter != m_objects->getObjects().end(); iter++)
	{
		std::cout << "Object coords: x:" << (* iter)->getPosition().x << " y:" << (*iter)->getPosition().y << " z:" << (*iter)->getPosition().z << std::endl;
	}
	return value;
}


void Game::createWindow(int windowWidth, int windowHeight)
{
	glfwSetErrorCallback(Game::errorCallback);
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
    window = glfwCreateWindow(windowWidth, windowHeight, "Crion World", NULL, NULL);
	if(!window)
		exit(EXIT_FAILURE);
	glfwMakeContextCurrent(window);
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
	glfwDestroyWindow(window);
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
	m_objects->render(pipe, * m_pLightingEffect);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
}

void Game::renderPass()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pLightingEffect->enable();
	renderPointLights();
	renderSpotLights();
	renderLightEffects();
	pipe->setCamera(gameCamera->GetPos(), gameCamera->GetTarget(), gameCamera->GetUp());
	m_objects->render(pipe, * m_pLightingEffect);
}

void Game::render()
{
	m_scale += 0.0057f;
	pipe->render();

	shadowMapPass();
	renderPass();

	glfwSwapBuffers(window);
	glfwPollEvents();
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
	spotLight->diffuseIntensity = 0.9f;
	spotLight->color = glm::vec3(1.0f, 1.0f, 1.0f);
	spotLight->position = gameCamera->GetPos();
	spotLight->direction = gameCamera->GetTarget();
	spotLight->attentuation.linear = 0.5f;
	spotLight->cutoff = 5.0f;
	m_pLightingEffect->setSpotLights(1, spotLight);

}

void Game::renderLightEffects()
{
	m_pLightingEffect->setWVP(* pipe->getTrans());
	m_pLightingEffect->setWorldMatrix(* pipe->getWorldTrans());
	m_pLightingEffect->setNormalMatrix(glm::transpose(glm::inverse(glm::mat3((*pipe->getWorldTrans())))));
	m_pLightingEffect->setEyeWorldPos(gameCamera->GetPos());
	m_pLightingEffect->setSpecularIntensity(1.0f);
	m_pLightingEffect->setSpecularPower(32);
	m_pLightingEffect->setDirectionalLight(*m_directionalLight);
	pipe->setCamera(spotLight->position, spotLight->direction, glm::vec3(0.0f, 1.0f, 0.0));
	m_pLightingEffect->setLightMatrix(* pipe->getTrans());

}

Object_manager * Game::getObjects()
{
	return m_objects;
}

GLFWwindow * Game::getWindow()
{
	return window;
}

void Game::onKeyboard(GLFWwindow * window, int key, int action)
{

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void Game::onKeyboardCharacters(GLFWwindow * window, unsigned int character)
{
		switch(character)
		{
		case GLFW_KEY_A:
			m_directionalLight->ambientIntensity += 0.05f;
			break;
		case GLFW_KEY_S:
			m_directionalLight->ambientIntensity -= 0.05f;
			break;
		case GLFW_KEY_Z:
			m_directionalLight->diffuseIntensity += 0.05f;
			break;
		case GLFW_KEY_X:
			m_directionalLight->diffuseIntensity -= 0.05f;
			break;
		}

	//if(m_directionalLight->ambientIntensity < 0.0f)
	//	m_directionalLight->ambientIntensity = 0.0f;

}

void Game::errorCallback(int error, const char* description)
{
	std::cout << error << " " << description << std::endl;
}

void Game::keyboardWrapper(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	cam->onKeyboard(window, key, action);
	game->onKeyboard(window, key, action);

}

void Game::keyboardCharactersWrapper(GLFWwindow * window, unsigned int character)
{
	game->onKeyboardCharacters(window, character);
	cam->onKeyboardCharacters(window, character);
}

void Game::mouseButtonWrapper(GLFWwindow * window, int button, int action, int mods)
{
	cam->onMouseButton(window, button, action);
}

void Game::mousePosWrapper(GLFWwindow * window, double x, double y)
{
	cam->onMousePos(window, x, y);
}

Game::~Game()
{
	delete m_pShadowMapEffect;
	delete gameCamera;
	delete pipe;
	delete m_pLightingEffect;
	delete pointLight;
	delete m_directionalLight;
}
