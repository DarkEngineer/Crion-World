#include "game.h"
#include "Textures.h"


Game::Game()
{}

Game::~Game()
{
}



void Game::makeProgram(GLuint & program)
{
	crionProgram = & program;
	if( !glIsProgram(* crionProgram) )
		* crionProgram = glCreateProgram();
}

