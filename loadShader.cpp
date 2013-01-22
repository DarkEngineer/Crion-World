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
