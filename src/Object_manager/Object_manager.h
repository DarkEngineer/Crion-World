#ifndef Object_manager_h
#define Object_manager_h
#include "../Player/Player.h"
#include "../Lighting/LightingTechnique.h"
#include "../Landscape/Landscape.h"
#include <memory>

template < class lType >
class Object_manager
{
	Player player;
	std::vector <std::unique_ptr<Object>> objects;
	std::vector <lType> objects;


public:
	Player & getPlayer();
	std::vector <std::unique_ptr<Object>> & getObjects();
	bool addPlayer(const char * sourceMesh, const char * fileStructure);
	bool addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	bool addObject(const char * sourceMesh, const char * fileStructure);
	bool addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	//bool addObject(lType object, glm::vec3 & position, const char * fileStructure);
	virtual void render();
	virtual void render(Pipeline * manager, LightingTechnique & position_reader);

	Object_manager();
	virtual ~Object_manager();
};
#endif