#include "loadshader.h"

#include "loadImage.h"




int main( int argc, char * argv[])
{

	printf( "Sciezka pliku to: %s\n", argv[ 0 ] );
	
	glfwInit();
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

	glewExperimental = GL_TRUE;
	glewInit();
	

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

    GLint retParam;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retParam);
    if(retParam != GL_TRUE)
    {
		GLint errorMsgLen = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &errorMsgLen);
		if (errorMsgLen > 0)
		{
			GLsizei charsWritten = 0;
			GLchar *errorMsg = new GLchar[errorMsgLen];
			glGetShaderInfoLog(fragmentShader, errorMsgLen, &charsWritten, errorMsg);
			fprintf(stderr, "Compilation error in shader %s: %s\n", "fragmentShader", errorMsg);
			
			
		 }
    }

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

;
	if(!Texture.Load( "sample.png" ))
		fprintf( stderr, "Failed to load texture file" );
	Texture.Bind();
	


	
	glfwEnable( GLFW_STICKY_KEYS );
 
	while( glfwGetWindowParam( GLFW_OPENED ) )
	{
   
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // Swap buffers
		glfwSwapBuffers();


		if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
 			break;
 
	} // Check if the ESC key was pressed or the window was closed
	
	

	glDeleteProgram( shaderProgram );
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	glDeleteBuffers(1, & ebo);
	glDeleteBuffers(1,  & vbo );
	glDeleteVertexArrays(1, &vao );

	
	
	glfwTerminate();
	return 0;
}
