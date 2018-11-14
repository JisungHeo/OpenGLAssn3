#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#define NUM_FACES 41215
class Bullet
{
public:
	Bullet(int direction, float x, float y,float z);
	~Bullet();
	void draw();
	void initVAO();
	void initVertices();
	void move();
	bool wallCollision();
	void rotation();
	float x, y, z;
	float x_diff, y_diff;
	float rotateAngle;
	vector<glm::vec3> vertices;
	GLuint VertexArrayID;
	int direction; //0: up, 1:down, 2:left, 3:right
};


