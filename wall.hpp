#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

using namespace std;
class Wall {
public:
	Wall(float x, float y, float z);
	float x;
	float y;
	float z;
	static glm::vec3 vertices[8];
	static int indices[24];
	static float uv[48];
	static GLuint Texture;
	static glm::vec3 out_vertices[24];
	static GLuint vertexArrayID;
	void draw();
	static void initVAO();
	static void initMap();
	static vector<Wall> vectorWall;
	static void drawAll();
	static GLfloat normals[72];
};