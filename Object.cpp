#include "Object.h"
#include "loadShader.h"

Object::Object()
{
}
Object::Object(GLuint vbo, float dx, float dy, bool objPoint, GLuint program )
{
  float width = 800;
	float height = 600;
	float x, y;
	if( dx == width/2 )
		x = 0.0;
	if( dx > width/2 )
		x = (dx - width/2)/ (width/2);
	else
		x = (dx - width/2) / (width/2);
	if(dx == height/2 )
		y = 0.0;
	if( dy == height/2 )
		y = (dy - height/2) / (height/2);
	else
		y = (dy - height/2) / -(height/2);
	vecVertices.push_back(x);
	vecVertices.push_back(y);
	
		/*glBufferSubData(GL_ARRAY_BUFFER, vecVertices.size() - 1, sizeof( float ) * vecVertices[0] * 2, & vecVertices[0]);*/
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	if( objPoint == true )
	{
		const std::string vShaderString = loadShaderFile( "object.vs" ).c_str();
	const GLchar * tempVShader = vShaderString.c_str();
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource(vertexShader, 1, & tempVShader, NULL);
	glCompileShader( vertexShader );
	getShaderLogInfo( vertexShader );

		const std::string fSource = loadShaderFile( "object.fs" ).c_str();
		const GLchar * fragmentSource = fSource.c_str();
		GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fShader, 1, & fragmentSource, NULL );
		glCompileShader( fShader );
		getShaderLogInfo( fShader );
		
	}

	/*glBindFragDataLocation( * vProgram, 0, "outColor" );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );*/
	
}

Object::~Object()
{
}
