#include "game.h"
#include "loadTexture.h"

Object::Object()
{
}
Object::Object(float _x, float _y, float _width, float _height)
  :	x( _x),
		y( _y),
		width(_width),
		height(_height)
	{
	}


Game::~Game()
{
}

void GameIntro::createWindow(int width, int height )
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

void GameIntro::loadObjects(std::vector<Object> modelObject)
{
	std::fstream sourceOfImages;
	std::string name = "gameIntro.txt";
	sourceOfImages.open(name, ios::in );
	if( sourceOfImages.good() == true )
	{
		std::cout << "Access to file " << name << " authorized" << std::endl;
		while( !sourceOfImages.eof() )
			name = "";
			std::getline( sourceOfImages, name );
			Object temp;
			modelObject.push_back( temp );
			temp.image = name.c_str();	
			std::cout << "Image " << name << " loaded" << endl;
	}
	else
		std::cout << "Access denied" << endl;
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
