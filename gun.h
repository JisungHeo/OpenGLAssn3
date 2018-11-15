#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
using namespace std;

class Gun
{
public:
	Gun();
	void draw();
	void initVAO();
	GLuint VertexArrayID;
	int dummy_obj_size;
};

