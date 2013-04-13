#ifndef GameIntro_h
#define GameIntro_h
#include "game.h"
#include "LightingTechnique.h"
#include "Mesh.h"


class GameIntro : public Game
{	
	Mesh Object;
	int window_width;
	int window_height;
	GLuint m_VBO;
	GLuint m_IBO;
	LightingTechnique* m_pEffect;
	Camera* m_pGameCamera;
	Texture* m_pTexture;
	float m_scale;
	DirectionalLight m_directionalLight;
	void createVertexBuffer();
	void createIndexBuffer();
public:
	GameIntro();
	Game * nextGameState();
	void setWindow(int width, int height);
	bool init();
	void render();
	void Update();
	virtual ~GameIntro();
};
#endif
