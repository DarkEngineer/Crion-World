#include "game.h"
#include "loadTexture.h"


Game::Game()
	:	maxObjects(100),
		i(0)
{}

Game::~Game()
{
}
void Game::makeBuffer()
{
	GLuint *vVbo = & vbo;
	if( !glIsBuffer( *vVbo ) )
		glGenBuffers( 1, vVbo);
		glBindBuffer( GL_ARRAY_BUFFER, *vVbo );
		
}

void Game::makeProgram(GLuint program)
{
	Game::crionProgram = & program;
	if( !glIsProgram(* crionProgram) )
		* crionProgram = glCreateProgram();
}

