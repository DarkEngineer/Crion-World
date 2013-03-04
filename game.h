#ifndef game_h
#define game_h
#include "includes.h"
#include "Object.h"

class Game
{
public:
	double i;
	GLuint vbo;
	GLuint * crionProgram;
	GLsizeiptr maxObjects;
	std::vector<Object> listOfObjects;
	virtual void render() =0;
	virtual void reserveSpace() =0;
	virtual void Update() =0;
	virtual void setWindow(int width, int height) =0;
	virtual Game * nextGameState() =0;
	virtual void makeBuffer();
	virtual void makeProgram(GLuint program);
	Game();
	virtual ~Game();
	
};


#endif
