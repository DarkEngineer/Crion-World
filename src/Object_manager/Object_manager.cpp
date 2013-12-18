#include "Object_manager.h"

Object_manager::objectData::objectData()
{
	s_position = glm::vec3(0.0f, 0.0f, 0.0f);
	s_fileStructure = NULL;
	s_sourceMesh = NULL;
}

Object_manager::Object_manager()
{
}


Player & Object_manager::getPlayer()
{
	return player;
}


std::vector <std::unique_ptr<Object>> & Object_manager::getObjects()
{
	return m_objects;
}


bool Object_manager::addPlayer(const char * sourceMesh, const char * fileStructure)
{

	return player.ifCreated(player.create(sourceMesh, fileStructure));

}


bool Object_manager::addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	return player.ifCreated(player.create(position, sourceMesh, fileStructure));
}


bool Object_manager::addObject(const char * sourceMesh, const char * fileStructure)
{
	m_objects.push_back(std::unique_ptr<Object>(new Object(sourceMesh, fileStructure)));
	std::cout << "LOG: Object " << sourceMesh << " created without coordinates" << std::endl; 

	return true;
}


bool Object_manager::addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	m_objects.push_back(std::unique_ptr<Object>(new Object(position, sourceMesh, fileStructure)));
	std::cout << "LOG: Object " << sourceMesh << " created" << std::endl; 

	return true;
}

template <class T>
bool Object_manager::addObject(T object, glm::vec3 & position, const char * fileStructure, const char * sourceMesh)
{
	

}


void Object_manager::render()
{
	if(player.getCreateStatus())
		player.render();

	std::vector <std::unique_ptr<Object>>::iterator count;
	for(count = m_objects.begin(); count != m_objects.end(); count++)
		(*count)->render();
}


void Object_manager::render(Pipeline * manager, LightingTechnique & position_reader)
{
	if(player.getCreateStatus())
	{
		position_reader.setWorldMatrix(* player.getPipeline().getWorldTrans());
		manager->worldPos(player.getPosition().x, player.getPosition().y, player.getPosition().z);
		position_reader.setNormalMatrix(manager->getNormalMatrix());
		position_reader.setWVP(* manager->getTrans());
		player.render();
	}

	if(m_objects.size() > 0)
	{
		std::vector <std::unique_ptr<Object>>::iterator count;
		for(count = m_objects.begin(); count != m_objects.end(); count++)
		{
			position_reader.setWorldMatrix(*(*count)->getPipeline().getWorldTrans());
			manager->worldPos((*count)->getPosition().x, (*count)->getPosition().y, (*count)->getPosition().z);
			position_reader.setNormalMatrix(manager->getNormalMatrix());
			position_reader.setWVP(*manager->getTrans());
			(* count)->render();
		}
	}
}


Object_manager::~Object_manager()
{
}