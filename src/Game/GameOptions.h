#ifndef GameOptions_h
#define GameOptions_h
#include "game.h"

class GameOptions : public Game
{
	void setWindow(int width, int height);
	void changeWindowSize( int width, int height );
	void render();
	void Update();
	Game * nextGameState();
};

#endif