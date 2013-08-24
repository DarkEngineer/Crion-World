#ifndef Game_h
#define Game_h
#include "../Pipeline/Pipeline.h"
#include "../FBOShadow/FrameBufferShadowMap.h"
#include "../ShadowMapTechnique/ShadowMapTechnique.h"
#include "../Object_manager/Object_manager.h"
#include "../Skybox/Skybox.h"
#include <string>

class Game
{
	GLFWwindow * m_pWindow;
	LightingTechnique * m_pLightingEffect;
	ShadowMapTechnique * m_pShadowMapEffect;
	ShadowMap * m_pShadowMap;
	Pipeline * m_pPipe;
	Camera * m_pGameCamera;
	float m_scale;
	DirectionalLight * m_pDirectionalLight;
	PointLight * m_pPointLight;
	SpotLight * m_pSpotLight;
	Object_manager * m_pObjects;
	Skybox * m_pSkybox;


	struct
	{
		int m_windowWidth;
		int m_windowHeight;
	};

	bool initLight();
	bool initModels();
	bool initSkybox();
	bool initCallbacks();
	void initDirectionaLights();
	void initPointLights();
	void initSpotLights();
	void renderPointLights();
	void renderSpotLights();
	void renderLightEffects();
	virtual void shadowMapPass();
	virtual void renderPass();
	void addObjects();

public:
	Game();
	virtual ~Game();

	void createWindow(int windowWidth, int windowHeight);
	void destroyWindow();

	bool init();
	virtual void render(); // main render function use it in main class for rendering
	Object_manager * getObjects();
	GLFWwindow * getWindow();

	void onKeyboard(GLFWwindow* window, int key, int action);
	void onKeyboardCharacters(GLFWwindow * window, unsigned int character);
	static void errorCallback(int error, const char* description);
	static void keyboardWrapper(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void keyboardCharactersWrapper(GLFWwindow * window, unsigned int character);
	static void mousePosWrapper(GLFWwindow* window, double x, double y);
	static void mouseButtonWrapper(GLFWwindow * window, int button, int action, int mods);
};

extern Game * game;
#endif