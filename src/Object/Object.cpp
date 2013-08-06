#include "Object.h"

Object::Object()
	: 
	position(glm::vec3(0.0f, 0.0f, 0.0f)),
	status(STATIC),
	physics(DISABLE),
	mesh(new Mesh()),
	matrices_manager(new Pipeline())

{
}

Object::Object(glm::vec3 & position, const char * sourceMesh, const char * fileStructure)
	:
	position(position),
	status(STATIC),
	physics(DISABLE),
	mesh(new Mesh()),
	matrices_manager(new Pipeline())
{
	mesh->setTexturePath(fileStructure);
	mesh->loadMesh(sourceMesh);
	matrices_manager->worldPos(position.x, position.y, position.z);
	pos_matrix = * matrices_manager->getWorldTrans();



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
		matrices_manager->worldPos(position.x, position.y, position.z);
		matrices_manager->scale(1.0f, 1.0f, 1.0f);
		matrices_manager->rotate(0.0f, 0.0f, 0.0f);
		pos_matrix = * matrices_manager->getWorldTrans();

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
		matrices_manager->worldPos(position.x, position.y, position.z);
		matrices_manager->scale(1.0f, 1.0f, 1.0f);
		matrices_manager->rotate(0.0f, 0.0f, 0.0f);
		pos_matrix = * matrices_manager->getWorldTrans();
		return true;
	}
	else
		return false;
}

const glm::vec3 Object::getPosition()
{
	return position;
}

Pipeline & Object::getPipeline()
{
	return * matrices_manager;
}

glm::mat4 Object::getPositionMatrix()
{
	return pos_matrix;
}
Object::~Object()
{
	delete mesh;
	delete matrices_manager;

}