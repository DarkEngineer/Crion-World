#include "loadshader.h"

int main()
{
	
	glfwInit();
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Crion World Alpha");
		
	glewExperimental = GL_TRUE;
	glewInit();
	
	GLuint vertexBuffer;
	glGenBuffers( 1, &vertexBuffer );
	printf( "%u\n", vertexBuffer );

	GLuint vao;
	glGenVertexArrays(1, & vao);
	glBindVertexArray( vao );

	GLuint vbo;
	glGenBuffers( 1, &vbo); //generate 1 buffer
	
	float vertices[] = {
		0.0f,	0.5f,
		0.5f,	-0.5f,
		-0.5f,	-0.5f
	};

	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

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
	glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	while( glfwGetWindowParam( GLFW_WINDOW ) )
	{
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		glDrawArrays( GL_TRIANGLES, 0, 3);
		glfwSwapBuffers();
		
	}

	glDeleteProgram( shaderProgram );
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	glDeleteBuffers(1,  & vbo );
	glDeleteVertexArrays(1, &vao );
	
	glfwTerminate();
	return 0;
}
