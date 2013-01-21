#include <stdio.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\glfw.h>


int main()
{
  glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Crion World Alpha");
	while( glfwGetWindowParam( GLFW_WINDOW ) )
	{
		glfwSwapBuffers();
	}

	if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
		return 0;
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vertexBuffer;
	glGenBuffers( 1, &vertexBuffer );

	printf( "%u\n", vertexBuffer);
	 
	float vertices[] = {
		0.0f,	0.5f,
		0.5f,	-0.5f,
		-0.5f,	-0.5f
	};

	glfwTerminate();
	return 0;
}
