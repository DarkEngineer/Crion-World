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

	// template for creating new objects in Object Manager
	// structure add new Object to s_m_obj then creating object with number in map s_m_obj_map
	template <typename T>
	struct s_Objects
	{
		std::vector <objectData> s_m_obj;
		std::map <unsigned int, T > s_m_obj_map;

		bool addObject(T object, glm::vec3 & position, const char * fileStructure, const char * sourceMesh)
		{
			objectData t_data;
			t_data.s_position = position;
			t_data.s_fileStructure = fileStructure;
			t_data.s_sourceMesh = sourceMesh;
			s_m_obj.push_back(t_data);
			s_m_obj_map[s_m_obj.size() - 1] = object

		}
	};

	Player player;
	std::vector <std::unique_ptr<Object>> m_objects;


public:
	Player & getPlayer();
	std::vector <std::unique_ptr<Object>> & getObjects();
	bool addPlayer(const char * sourceMesh, const char * fileStructure);
	bool addPlayer(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	bool addObject(const char * sourceMesh, const char * fileStructure);
	bool addObject(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	// method for creating new object, it uses template and builded method in private structure s_Objects
	template <typename T>
	bool addObject(T object, glm::vec3 & position, const char * fileStructure, const char * sourceMesh)
	{
		typename s_Objects<T>::addObjects(object, position, fileStructure, sourceMesh);
	}
	virtual void render();
	virtual void render(Pipeline * manager, LightingTechnique & position_reader);

	Object_manager();
	virtual ~Object_manager();
};
#endif