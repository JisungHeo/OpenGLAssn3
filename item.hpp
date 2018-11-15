#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
using namespace std;
class Item
{
public:
	Item(int type, float x, float y);
	void draw();
	bool playerCollision();
	float x,y,z;
	int type;// subclasses
	static GLuint vertexArrayID;
	static int verticesSize;
	static vector<Item> vectorItem;
	static void initVAO();
	static void initMap();
	static void drawAll();
};