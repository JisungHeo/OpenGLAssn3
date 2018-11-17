#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#define NUM_FACES 41215
using namespace std;

class Bullet
{
public:
	Bullet(float direction, float x, float y);
	~Bullet();
	void draw();
	static void initVAO();
	void move();
	bool wallCollision();
	void rotation();
	static void update();
	static void drawAll();
	float x, y, z;
	float x_diff,y_diff;
	float rotateAngle;
	static GLuint VertexArrayID;
	static int dummy_obj_size;
	static vector<Bullet> vectorBullet;
	float direction; //0:, 1:down, 2:left, 3:right
};