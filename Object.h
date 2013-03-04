#ifndef Object_h
#define Object_h
#include "includes.h"

class Object
{
public:
  GLuint texture;
	GLuint vao;
	GLuint vShader;
	GLuint fShader;
	std::string image;
	std::vector <float> vecVertices;
	enum states
	{
		OBJ_SELECTED = 1,
		OBJ_UNSELECTED = 0
	};
	Object();
	Object(GLuint vbo, float dx, float dy, bool objPoint, GLuint program );
	~Object();
};
#endif
