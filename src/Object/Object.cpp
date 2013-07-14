#include "Object.h"

Object::Object()
{
	pos_manager = new Pipeline();
	mesh = new Mesh();
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Object::render()
{
}

Object::~Object()
{
	delete pos_manager;
	delete & position;
	delete mesh;
	delete & state;
	delete & status;
	delete & physics;

}