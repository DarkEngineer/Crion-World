#include "Object_manager.h"

Object_manager::Object_manager()
	:
	player(0)
{
}

Player * Object_manager::getPlayer()
{
	return player;
}

std::vector <std::unique_ptr<Object>> & Object_manager::getObjects()
{
	return objects;
}

bool Object_manager::addPlayer(const char * sourceMesh, const char * fileStructure)
{
	player = new Player();
	return player->create(sourceMesh, fileStructure);

}

bool Object_manager::addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	player = new Player();
	return player->create(position, sourceMesh, fileStructure);
}

bool Object_manager::addObject(const char * sourceMesh, const char * fileStructure)
{
	objects.push_back(std::unique_ptr<Object>(new Object(sourceMesh, fileStructure)));
	std::cout << "LOG: Object " << sourceMesh << " created without coordinates" << std::endl; 

	return true;
}

bool Object_manager::addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	objects.push_back(std::unique_ptr<Object>(new Object(position, sourceMesh, fileStructure)));
	std::cout << "LOG: Object " << sourceMesh << " created" << std::endl; 

	return true;
}

void Object_manager::render()
{
	if(player != 0)
		player->render();
	std::vector <std::unique_ptr<Object>>::iterator count;
	for(count = objects.begin(); count != objects.end(); count++)
		(*count)->render();
}

void Object_manager::render(LightingTechnique & manager_position)
{
	if(player != 0)
		
}

Object_manager::~Object_manager()
{
	delete player;
	objects.clear();
}

