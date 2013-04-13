#ifndef GameMenu_h
#define GameMenu_h
#include "game.h"

class GameMenu : public Game
{
	void setWindow(int width, int height);
	void render();
	void Update();
	Game * nextGameState();

};

#endif