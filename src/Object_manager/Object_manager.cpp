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

std::vector <Object> Object_manager::getObjects()
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
	Object temp;
	if(temp.create(sourceMesh, fileStructure))
	{
		objects.push_back(temp);
		return true;
	}
	else
	{
		return false;
	}
}

bool Object_manager::addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	Object * temp = new Object();
	bool value = false;
	if(temp->create(position, sourceMesh, fileStructure))
	{
		objects.push_back(*temp);
		std::cout << "LOG: Object " << sourceMesh << " created" << std::endl; 
		value = true;
	}
	return value;
}

void Object_manager::render()
{
	if(player != 0)
		player->render();
	std::vector <Object>::iterator count;
	for(count = objects.begin(); count != objects.end(); count++)
		count->render();
	std::cout << objects.size() << std::endl;
}

Object_manager::~Object_manager()
{
	delete player;
}

