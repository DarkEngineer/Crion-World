#include "Object.h"

Object::Object()
	: 
	position(glm::vec3(0.0f, 0.0f, 0.0f)),
	status(STATIC),
	physics(DISABLE)
{
	mesh = new Mesh();
	pos_manager = new Pipeline();
}

Object::Object(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
}

Object::Object(const char * sourceMesh, const char * fileStructure)
{
}


void Object::init(glm::vec3 & position)
{
	//require bounding box for details
}
void Object::render()
{
	mesh->render();
}


bool Object::create(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
{
	this->position = position;
	if(mesh->setTexturePath(fileStructure))
	{
		mesh->loadMesh(sourceMesh);
		pos_manager->worldPos(position.x, position.y, position.z);
		pos_matrix = * pos_manager->getWorldTrans();

		return true;
	}
	else
		return false;

}

bool Object::create(const char * sourceMesh, const char * fileStructure)
{
	if(mesh->setTexturePath(fileStructure))
	{
		mesh->loadMesh(sourceMesh);
		pos_manager->worldPos(position.x, position.y, position.z);
		pos_matrix = * pos_manager->getWorldTrans();
		return true;
	}
	else
		return false;
}



Object::~Object()
{
	delete mesh;
	delete pos_manager;

}