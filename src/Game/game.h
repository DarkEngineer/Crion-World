#ifndef game_h
#define game_h
#include "includes.h"
#include "Camera.h"
#include "Textures.h"

class Game
{
public:
	double i;
	GLuint * crionProgram;
	GLsizeiptr maxObjects;
	virtual bool init() =0;
	virtual void render() =0;
	virtual void Update() =0;
	virtual void setWindow(int width, int height) =0;
	virtual Game * nextGameState() =0;
	virtual void makeProgram(GLuint & program);
	Game();
	virtual ~Game();
	
};


#endif
