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
	
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetWindowTitle("Crion World Alpha");
	game->init();
	Mesh * Obj = new Mesh();
	Obj->loadMesh("Studnia.3ds");
	glfwEnable( GLFW_STICKY_KEYS );
	glEnable(GL_DEPTH_TEST);
 
	while( glfwGetWindowParam( GLFW_OPENED ) )
	{
		 game->render();
		 game = game->nextGameState();
		Obj->render();

    // Swap buffers
		glfwSwapBuffers();


		if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
 			break;
 
	} // Check if the ESC key was pressed or the window was closed
	
	
	glfwTerminate();
	return 0;
}
