#include "loadshader.h"
#include "game.h"
#include "loadImage.h"
#include <SOIL\SOIL.h>
#include <time.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

int main( )
{
	Game * game = new GameIntro();
	game->setWindow(800, 600);
	
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetWindowTitle("Crion World Alpha");
	
	
	GLuint vertexBuffer;
	glGenBuffers( 1, &vertexBuffer );
	printf( "%u\n", vertexBuffer );


	GLuint vao;
	glGenVertexArrays(1, & vao);
	glBindVertexArray( vao );

	GLuint vbo;
	glGenBuffers( 1, &vbo); //generate 1 buffer
	
	GLuint ebo;
	glGenBuffers(1, &ebo);



	float vertices[] = {
		//Positiom    Color				Texture coords
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// top-right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f// bottom-left
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );
	
	// vertex shader loading
	const string vShaderString = loadShaderFile("SimpleVertexShader.vertexshader").c_str();
	const GLchar * tempVShader = vShaderString.c_str();
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource(vertexShader, 1, & tempVShader, NULL);
	glCompileShader( vertexShader ); 
	getShaderLogInfo( vertexShader );

	//fragment shader loading
	const string fShaderString = loadShaderFile("SimpleFragmentShader.fragmentshader").c_str();
	const GLchar * tempFShader = fShaderString.c_str();
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource(fragmentShader, 1, & tempFShader, NULL );
	glCompileShader(fragmentShader);
	getShaderLogInfo( fragmentShader );


	GLuint shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader);
	glBindFragDataLocation( shaderProgram, 0, "outColor" );
	glLinkProgram( shaderProgram );
	glUseProgram( shaderProgram );
	getProgramLogInfo( shaderProgram );

	GLint posAttrib = glGetAttribLocation( shaderProgram, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0 );
	
	GLint colAttrib =  glGetAttribLocation( shaderProgram, "color" );
	glEnableVertexAttribArray( colAttrib );
	glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)( 2*sizeof(float) ) );
	GLint texAttrib = glGetAttribLocation( shaderProgram, "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)( 5*sizeof(float) ) );

	glFITexture Texture;
	GLuint textures[ 2 ];
	glGenTextures( 2, textures );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, textures[ 0 ] );
	Texture.Load( "images\\sample.png" );
	Texture.Bind();
	glUniform1i( glGetUniformLocation( shaderProgram, "texKitten"), 0 );

	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, textures[ 1 ] );
	Texture.Load( "images\\sample2.png" );
	Texture.Bind();
	glUniform1i( glGetUniformLocation( shaderProgram, "texPuppy" ), 1 );

	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


	glfwEnable( GLFW_STICKY_KEYS );
 
	while( glfwGetWindowParam( GLFW_OPENED ) )
	{
		 game->render();
		 game = game->nextGameState();
		
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // Swap buffers
		glfwSwapBuffers();


		if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
 			break;
 
	} // Check if the ESC key was pressed or the window was closed
	
	
	glDeleteTextures( 2, textures );
	glDeleteProgram( shaderProgram );
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	glDeleteBuffers(1, & ebo);
	glDeleteBuffers(1,  & vbo );
	glDeleteVertexArrays(1, &vao );

	
	
	glfwTerminate();
	return 0;
}
