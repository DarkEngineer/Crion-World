#ifndef game_h
#define game_h
#include "includes.h"

class GameIntro
{
  void createWindow(int width, int height);
	void loadObjects( std::vector<Object> modelObject);
	void render();
	bool nextGameState();

};

class GameMenu
{
	void loadObjects( std::vector<Object> modelObject);
	void render();
	bool nextGameState();

};

class GameOptions
{
	void changeWindowSize( int width, int height );
	void loadObjects( std::vector<Object> modelObject);
	void render();
	bool nextGameState();
};

class GameMain
{
	void loadObjects( std::vector<Object> modelObject);
	void render();
	bool nextGameState();
};

class GameHighscores
{
	void loadObjects( std::vector<Object> modelObject);
	void loadHighscores();
	void render();
	void nextGameState();
};
#endif
