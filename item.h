/*#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
using namespace std;
class Item
{
public:
	Item(int type, float a, float y, float z);
	void draw();
	bool playerCollision();
	void initVAO();
	void initVertices();

	float x,y,z;
	int type;// subclasses
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	GLuint VertexArrayID;
};*/