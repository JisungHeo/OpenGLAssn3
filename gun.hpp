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
	Gun(float,float);
	void draw();
	static void initVAO();
	static GLuint VertexArrayID;
	static int dummy_obj_size;
	float x, y;

};

