#ifndef GameMain_h
#define GameMain_h
#include "game.h"

class GameMain : public Game
{
	void setWindow(int width, int height);
	void render();
	void Update();
	Game * nextGameState();
};
#endif