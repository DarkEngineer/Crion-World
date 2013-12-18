#ifndef Object_manager_h
#define Object_manager_h
#include "../Player/Player.h"
#include "../Lighting/LightingTechnique.h"
#include "../Landscape/Landscape.h"
#include <memory>
#include <map>

class Object_manager
{
	struct objectData
	{
		glm::vec3 s_position;
		const char * s_fileStructure;
		const char * s_sourceMesh;

		objectData();
		~objectData();
	};


	Player player;
	std::vector <std::unique_ptr<Object>> m_objects;

	std::vector <objectData> m_obj;
	template <class T>
	std::map <unsigned int, T> m_obj_map;

public:
	Player & getPlayer();
	std::vector <std::unique_ptr<Object>> & getObjects();
	bool addPlayer(const char * sourceMesh, const char * fileStructure);
	bool addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	bool addObject(const char * sourceMesh, const char * fileStructure);
	bool addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	template <class T>
	bool addObject(T object, glm::vec3 & position, const char * fileStructure = NULL, const char * sourceMesh = NULL);
	virtual void render();
	virtual void render(Pipeline * manager, LightingTechnique & position_reader);

	Object_manager();
	virtual ~Object_manager();
};
#endif