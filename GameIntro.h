#ifndef GameIntro_h
#define GameIntro_h
#include "game.h"

class GameIntro : public Game
{  
public:
	GameIntro();
	void reserveSpace();
	void createObject();
	void drawObjects();
	Game * nextGameState();
	void setWindow(int width, int height);
	void imageHandle();
	void render();
	void Update();
	~GameIntro();
};
#endif
