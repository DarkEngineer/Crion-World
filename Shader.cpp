#include "Shader.h"

Shader::Shader()
{
	shader = 0;
}

GLuint Shader::getShader() 
{
	return this->shader;
}
void Shader::attachShader( GLuint program )
{
	glAttachShader( program, shader );
}

GLuint Shader::createShaderFromFile( std::string name, ShaderType type)
{
	objShaderType = type;
	source = name;
	if( type == VERTEX_SHADER )
	{
		const std::string ShaderString = loadShaderFile( source ).c_str();
		const GLchar * tempShader = ShaderString.c_str();
		shader = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource(shader, 1, & tempShader, NULL);
		glCompileShader( shader );
		getShaderLogInfo( shader );
	}

	if( type == FRAGMENT_SHADER )
	{
		const std::string ShaderString = loadShaderFile( source ).c_str();
		const GLchar * tempShader = ShaderString.c_str();
		shader = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource(shader, 1, & tempShader, NULL);
		glCompileShader( shader );
		getShaderLogInfo( shader );
	}

	if( type == GEOMETRY_SHADER )
	{
		const std::string ShaderString = loadShaderFile( source ).c_str();
		const GLchar * tempShader = ShaderString.c_str();
		shader = glCreateShader( GL_GEOMETRY_SHADER );
		glShaderSource(shader, 1, & tempShader, NULL);
		glCompileShader( shader );
		getShaderLogInfo( shader );
	}

	if( type == TESS_CONTROL_SHADER )
	{
		const std::string ShaderString = loadShaderFile( source ).c_str();
		const GLchar * tempShader = ShaderString.c_str();
		shader = glCreateShader( GL_TESS_CONTROL_SHADER );
		glShaderSource(shader, 1, & tempShader, NULL);
		glCompileShader( shader );
		getShaderLogInfo( shader );
	}

	if( type == TESS_EVALUATION_SHADER )
	{
		const std::string ShaderString = loadShaderFile( name ).c_str();
		const GLchar * tempShader = ShaderString.c_str();
		shader = glCreateShader( GL_TESS_EVALUATION_SHADER );
		glShaderSource(shader, 1, & tempShader, NULL);
		glCompileShader( shader );
		getShaderLogInfo( shader );
	}

	return shader;
}
std::string Shader::loadShaderFile(const std::string fileName)
{
	
	std::ifstream shaderFile( fileName.c_str());

	//find the file size
	shaderFile.seekg(0, std::ios::end);
	std::streampos length = shaderFile.tellg();
	shaderFile.seekg(0, std::ios::beg);

	//read whole file into a vector
	std::vector<char> buffer(length);
	shaderFile.read(&buffer[0], length);

	//return the shader string
	return std::string( buffer.begin(), buffer.end());
}

void Shader::getShaderLogInfo( GLuint shader )
{
	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, & status );
	if( status == GL_TRUE )
	{
		std::cout << "SHADER SUCCESSFULLY LOADED" << std::endl;
		
	}
	else 
	{
		std::cout << "SHADER DIDN'T LOAD" << std::endl;
		std::fstream logs;
		logs.open( "logs.txt", std::ios::in | std::ios::out | std::ios::trunc );
		char buffer[ 512 ] ;
		glGetShaderInfoLog( shader, 512, NULL, buffer );
		logs << buffer;
		logs.close();
		glfwInit();
		GLint retParam;
		 glGetShaderiv(shader, GL_COMPILE_STATUS, &retParam);
		if(retParam != GL_TRUE)
		{
			GLint errorMsgLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorMsgLen);
			if (errorMsgLen > 0)
			{
				GLsizei charsWritten = 0;
				GLchar *errorMsg = new GLchar[errorMsgLen];
				glGetShaderInfoLog(shader, errorMsgLen, &charsWritten, errorMsg);
				fprintf(stderr, "Compilation error in shader %s: %s\n", "Shaders", errorMsg);
			
			
			}
		}
		glDeleteShader( shader );
	}

	return;
}

void Shader::getProgramLogInfo( GLuint program )
{
	GLint status;
	glGetProgramiv( program, GL_LINK_STATUS, & status );
	if( status == GL_TRUE )
		std::cout << "PROGRAM SUCCESSFULLY LOADED" << std::endl;
	else
	{
		std::cout << "PROGRAM DIDN'T LOAD" << std::endl;
		std::fstream logs;
		logs.open( "logs.txt", std::ios::in | std::ios::out | std::ios::trunc );
		char buffer[ 512 ] ;
		glGetProgramInfoLog( program, 512, NULL, buffer );
		logs << buffer;
		logs.close();
		glDeleteProgram( program );
	}

	return;
}
void Shader::DelShader()
{
	glDeleteShader( shader );
}

Shader::~Shader()
{
	glDeleteShader( shader );
}