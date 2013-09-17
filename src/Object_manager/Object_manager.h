#ifndef Object_manager_h
#define Object_manager_h
#include "../Player/Player.h"
#include "../Lighting/LightingTechnique.h"
#include "../Landscape/Landscape.h"
#include <memory>


class Object_manager
{
	Player player;
	std::vector <std::unique_ptr<Object>> objects;
	std::vector <std::unique_ptr<Landscape>> landscape;


public:
	Player & getPlayer();
	std::vector <std::unique_ptr<Object>> & getObjects();
	std::vector <std::unique_ptr<Landscape>> & getLandscapes();
	bool addPlayer(const char * sourceMesh, const char * fileStructure);
	bool addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	bool addObject(const char * sourceMesh, const char * fileStructure);
	bool addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	virtual void render();
	virtual void render(Pipeline * manager, LightingTechnique & position_reader);

	Object_manager();
	virtual ~Object_manager();
};
#endif