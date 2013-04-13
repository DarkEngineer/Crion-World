#include "game.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameIntro.h"
#include "glFreeImage.h"
#include <time.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


int main( )
{
	float width = 800.0f;
	float height = 600.0f;
	Game * game = new GameIntro();
	game->setWindow(static_cast<int>(width), static_cast<int>(height));
	glfwSetWindowTitle("Crion World Alpha");
	glfwEnable( GLFW_STICKY_KEYS );
 
	Mesh * mesh = new Mesh();
	mesh->loadMesh("Studnia.3ds");
	glEnable(GL_DEPTH_TEST);
	while( glfwGetWindowParam( GLFW_OPENED ) )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		mesh->render();
		 game = game->nextGameState();
		 
    // Swap buffers
		glfwSwapBuffers();

		if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
 			break;
 
	} // Check if the ESC key was pressed or the window was closed
	
	
	glfwTerminate();
	return 0;
}
