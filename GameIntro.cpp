#include "GameIntro.h"

GameIntro::GameIntro()
{
}

void GameIntro::reserveSpace()
{
  glBufferData( GL_ARRAY_BUFFER, maxObjects, & listOfObjects, GL_DYNAMIC_DRAW );
}
void GameIntro::createObject()
{
	i = 0;
	int x, y;
	glfwGetMousePos( &x, &y );
	Object obj(GameIntro::vbo, (float)x, (float)y, true, * crionProgram);
	if(listOfObjects.size() < maxObjects )
	{	listOfObjects.push_back( obj );
	std::cout << "Created object number " << listOfObjects.size() << std::endl;
	std::cout << x << " " << y << std::endl;
	GLintptr offset = listOfObjects.size() - 1;
	glBufferSubData(GL_ARRAY_BUFFER, offset, 1, & listOfObjects[ listOfObjects.size()-1 ] );
	}

}
void GameIntro::setWindow(int width, int height )
{
	glfwInit();
	
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow( width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

	glewExperimental = GL_TRUE;
	glewInit();
}

Game * GameIntro::nextGameState()
{
	return this;
}
void GameIntro::imageHandle()
{
	std::fstream sourceOfImages;
	std::string name = "gameIntro.txt";
	sourceOfImages.open(name, std::ios::in );
	if( sourceOfImages.good() == true )
	{
		std::cout << "Access to file " << name << " authorized" << std::endl;
		while( !sourceOfImages.eof() )
			name = "";
			std::getline( sourceOfImages, name );
			Object temp;
			listOfObjects.push_back( temp );
			temp.image = name.c_str();	
			std::cout << "Image " << name << " loaded" << std::endl;
	}
	else
		std::cout << "Access denied" << std::endl;
}

void GameIntro::render()
{
}

void GameIntro::Update()
{
}

GameIntro::~GameIntro()
{
}
