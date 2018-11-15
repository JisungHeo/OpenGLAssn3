#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
class Wall {
public:
	Wall(float x, float y);
	float x;
	float y;
	static glm::vec3 vertices[8];
	static int indices[24];
	static glm::vec3 out_vertices[24];
	static GLuint vertexArrayID;
	void draw();
	static void initVAO();
};