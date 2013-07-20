#ifndef Object_manager_h
#define Object_manager_h
#include "../Player/Player.h"


class Object_manager
{
	Player * player;
	std::vector <Object> objects;

public:
	Player * getPlayer();
	std::vector <Object> getObjects();
	virtual void addPlayer(const char * sourceMesh, const char * fileStructure);
	virtual void addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	virtual void addObject(const char * sourceMesh, const char * fileStructure);
	virtual void addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	virtual void render();

	Object_manager();
	virtual ~Object_manager();
};
#endif