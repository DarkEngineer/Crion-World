#ifndef Object_h
#define Object_h
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"

class Object
{
	//BoundingBox * box;
	glm::vec3 position;
	glm::mat4 pos_matrix;
	Mesh * mesh;
	Pipeline * pos_manager;


	enum Status
	{
		STATIC,
		DYNAMIC
	} status;

	enum Physic
	{
		ENABLE,
		DISABLE
	} physics;

	void init(glm::vec3 & position);

public:
	Object();
	virtual ~Object();

	virtual bool create(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	virtual bool create(const char * sourceMesh, const char * fileStructure);
	virtual void render();
};

#endif