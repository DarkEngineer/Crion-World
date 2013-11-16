#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <time.h>
#include "Game/Game.h"

 
int main()
{
	Game * application = new Game();
	game = application;
	if(!glfwInit())
		exit(EXIT_FAILURE);
	application->createWindow(800, 600);
	GLenum res = glewInit();
	if( res != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(res) << std::endl;
		return 0;
	}
	application->init();
	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(application->getWindow()))
	{
		application->render();
	}
	
	application->destroyWindow();
	glfwTerminate();
	return 0;
}