#ifndef game_h
#define game_h
#include "includes.h"

class Game
{
public:
	virtual void render() =0;
	virtual void Update() =0;
	virtual ~Game();
};

class GameIntro : public Game
{
	void createWindow(int width, int height);
	void loadObjects( std::vector<Object> modelObject);
	void render();
	Game * nextGameState();

};

class GameMenu : public Game
{
	void loadObjects( std::vector<Object> modelObject);
	void render();
	Game * nextGameState();

};

class GameOptions : public Game
{
	void changeWindowSize( int width, int height );
	void loadObjects( std::vector<Object> modelObject);
	void render();
	Game * nextGameState();
};

class GameMain : public Game
{
	void loadObjects( std::vector<Object> modelObject);
	void render();
	Game * nextGameState();
};

class GameHighscores : public Game
{
	void loadObjects( std::vector<Object> modelObject);
	void loadHighscores();
	void render();
	Game * nextGameState();
};
#endif
