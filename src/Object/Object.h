#ifndef Object_h
#define Object_h
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"

class Object
{
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

protected:
	//BoundingBox * box;
	glm::vec3 position;
	glm::mat4 pos_matrix;
	Mesh * mesh;
	Pipeline * pos_manager;

public:
	Object();
	Object::Object(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	Object::Object(const char * sourceMesh, const char * fileStructure);
	virtual ~Object();

	bool create(glm::vec3 & position, const char * sourceMesh, const char * fileStructure);
	bool create(const char * sourceMesh, const char * fileStructure);
	virtual void render();
};

#endif