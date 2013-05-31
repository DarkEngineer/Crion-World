#ifndef Game_h
#define Game_h
#include "../Lighting/LightingTechnique.h"
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"
#include <GL/glfw.h>

class Game
{
	LightingTechnique * m_pEffect;
	Camera * m_pGameCamera;
	float m_scale;
	DirectionalLight m_directionalLight;
	Mesh * mesh;
	struct
	{
		int m_windowWidth;
		int m_windowHeight;
	};
	

public:
	Game();
	~Game();

	void createWindow(int windowWidth, int windowHeight);

	bool init();
	virtual void render();

	void onKeyboard(int key, int action);
	static void GLFWCALL keyboardWrapper( int key, int action);
	static void GLFWCALL mousePosWrapper(int x, int y);
	static void GLFWCALL mouseButtonWrapper(int button, int action);
};

extern Game * game;
#endif