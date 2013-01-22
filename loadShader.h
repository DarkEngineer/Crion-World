#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <GL\glut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glfw.h>

using namespace std;

string loadShaderFile(const string fileName);
void getShaderLogInfo( GLuint shader );
void getProgramLogInfo( GLuint program );
