#ifndef Game_h
#define Game_h
#include "../Lighting/LightingTechnique.h"
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"
#include "../FBOShadow/FrameBufferShadowMap.h"
#include "../ShadowMapTechnique/ShadowMapTechnique.h"
#include <string>

class Game
{
	GLFWmonitor * monitor;
	GLFWwindow * window;
	LightingTechnique * m_pLightingEffect;
	ShadowMapTechnique * m_pShadowMapEffect;
	ShadowMap * m_shadowMap;
	Pipeline * pipe;
	Camera * gameCamera;
	float m_scale;
	DirectionalLight * m_directionalLight;
	PointLight * pointLight;
	SpotLight * spotLight;
	Mesh * mesh;
	struct
	{
		int m_windowWidth;
		int m_windowHeight;
	};
	bool initLight();
	bool initModels();
	bool initCallbacks();
	void initDirectionaLights();
	void initPointLights();
	void initSpotLights();
	void renderPointLights();
	void renderSpotLights();
	virtual void shadowMapPass();
	virtual void renderPass();

public:
	Game();
	virtual ~Game();

	void createWindow(int windowWidth, int windowHeight);
	void destroyWindow();

	bool init();
	virtual void render();
	Mesh * getMesh();
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