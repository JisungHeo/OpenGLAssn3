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
	void initVertices();
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	GLuint VertexArrayID;
};

