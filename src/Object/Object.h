#ifndef Object_h
#define Object_h
#include "../Mesh/Mesh.h"
#include "../Pipeline/Pipeline.h"

class Object
{
	//BoundingBox * box;
	Pipeline * pos_manager;
	glm::vec3 position;
	Mesh * mesh;
	enum
	{
		STANDING,
		RUNNING,
		DEAD,
		SHOOTING,
		SITTING
	} state;

	enum
	{
		STATIC,
		DYNAMIC
	} status;

	enum
	{
		ENABLE,
		DISABLE
	} physics;

	void init();
public:
	Object();
	virtual ~Object();

	virtual void render();
};

#endif