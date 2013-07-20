#include "Object_manager.h"

Object_manager::Object_manager()
{
	player = 0;
}

Player * Object_manager::getPlayer()
{
	return player;
}

std::vector <Object> Object_manager::getObjects()
{
	return objects;
}

void Object_manager::addPlayer(const char * sourceMesh, const char * fileStructure)
{
	player = new Player();
	player->create(sourceMesh, fileStructure);

}

void Object_manager::addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	player = new Player();
	player->create(position, sourceMesh, fileStructure);
}

void Object_manager::addObject(const char * sourceMesh, const char * fileStructure)
{
	Object temp;
	temp.create(sourceMesh, fileStructure);
	objects.push_back(temp);
}

void Object_manager::addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	Object temp;
	temp.create(position, sourceMesh, fileStructure);

}

Object_manager::~Object_manager()
{
	delete player;
	delete & objects;
}

