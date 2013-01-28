#ifndef game_h
#define game_h
#include "includes.h"
class Object;
class GameIntro;
class GameMenu;
class GameMain;
class GameOptions;
class GameHighscores;
class Game;

class Object
{
public:
		const char* image;
		float x;
		float y;
		float width;
		float height;
		GLuint VertexBuffer;
		GLuint vertexShader;
		GLuint fragmentShader;
	Object();
	Object( float x, float y, float width, float height );
};

class Game
{
	virtual void render() =0;
	virtual void Update() =0;
public:
	virtual ~Game();
	
};

class GameIntro : public Game
{

	void loadObjects( std::vector<Object> modelObject);
	
	Game * nextGameState();
public:
		void createWindow(int width, int height);
		void render();
		void Update();
		~GameIntro();
};

class GameMenu : public Game
{
	void loadObjects( std::vector<Object> modelObject);
	void render();
	void Update();
	Game * nextGameState();

};

class GameOptions : public Game
{
	void changeWindowSize( int width, int height );
	void loadObjects( std::vector<Object> modelObject);
	void render();
	void Update();
	Game * nextGameState();
};

class GameMain : public Game
{
	void loadObjects( std::vector<Object> modelObject);
	void render();
	void Update();
	Game * nextGameState();
};

class GameHighscores : public Game
{
	void loadObjects( std::vector<Object> modelObject);
	void loadHighscores();
	void render();
	void Update();
	Game * nextGameState();
};
#endif
