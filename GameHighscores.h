#ifndef GameHighscores_h
#define GameHighscores_h
#include "game.h"

class GameHighscores : public Game
{
	void setWindow(int width, int height);
	void loadHighscores();
	void render();
	void Update();
	Game * nextGameState();
};

#endif