#ifndef Game_h
#define Game_h
#include "../Lighting/LightingTechnique.h"
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"
#include <string>

class Game
{
	static const int fieldDepth = 1;
	LightingTechnique * m_pEffect;
	Pipeline * pipe;
	Camera * gameCamera;
	float m_scale;
	DirectionalLight m_directionalLight;
	PointLight * pointLight;
	Mesh * mesh;
	struct
	{
		int m_windowWidth;
		int m_windowHeight;
	};
	

public:
	Game();
	virtual ~Game();

	void createWindow(int windowWidth, int windowHeight);

	bool init();
	bool initLight();
	bool initModels();
	bool initCallbacks();
	virtual void render();
	Mesh * getMesh();

	void onKeyboard(int key, int action);
	static void GLFWCALL keyboardWrapper( int key, int action);
	static void GLFWCALL mousePosWrapper(int x, int y);
	static void GLFWCALL mouseButtonWrapper(int button, int action);
};

extern Game * game;
#endif