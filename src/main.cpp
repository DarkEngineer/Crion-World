 
#include <GL/glew.h>
#include <GL/glfw.h>
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
	application->createWindow(800, 600);
	GLenum res = glewInit();
	if( res != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(res) << std::endl;
		return 0;
	}
	application->init();
	glEnable(GL_DEPTH_TEST);

	glfwEnable(GLFW_KEY_REPEAT);

	while(glfwGetWindowParam(GLFW_OPENED) && !(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) )
	{
		application->render();
	}
	
	glfwTerminate();
	return 0;
}