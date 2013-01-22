#include "loadShader.h"

string loadShaderFile(const string fileName)
{
	
	ifstream shaderFile( fileName.c_str());

	//find the file size
	shaderFile.seekg(0, ios::end);
	std::streampos length = shaderFile.tellg();
	shaderFile.seekg(0, ios::beg);

	//read whole file into a vector
	vector<char> buffer(length);
	shaderFile.read(&buffer[0], length);

	//return the shader string
	return string( buffer.begin(), buffer.end());
}

void getShaderLogInfo( GLuint shader )
{
	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, & status );
	if( status == GL_TRUE )
		cout << "SHADER SUCCESSFULLY LOADED" << endl;
	else
	{
		cout << "SHADER DIDN'T LOAD" << endl;
		std::fstream logs;
		logs.open( "logs.txt", ios::in | ios::out | ios::trunc );
		char buffer[ 512 ] ;
		glGetShaderInfoLog( shader, 512, NULL, buffer );
		logs << buffer;
		logs.close();
		glDeleteShader( shader );
	}

	return;
}

void getProgramLogInfo( GLuint program )
{
	GLint status;
	glGetProgramiv( program, GL_LINK_STATUS, & status );
	if( status == GL_TRUE )
		cout << "PROGRAM SUCCESSFULLY LOADED" << endl;
	else
	{
		cout << "PROGRAM DIDN'T LOAD" << endl;
		std::fstream logs;
		logs.open( "logs.txt", ios::in | ios::out | ios::trunc );
		char buffer[ 512 ] ;
		glGetProgramInfoLog( program, 512, NULL, buffer );
		logs << buffer;
		logs.close();
		glDeleteProgram( program );
	}

	return;
}
