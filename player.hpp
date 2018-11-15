#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#define ArrSize 100
class Player {
public:
	Player(float x, float y);
	float x;
	float y;
	float direction;//degree x:0, y:90.0f, -x:180.0f, -y:270.0f
	static GLuint vertexArrayID;
	void draw();
	static void initVAO();
	static Player player;
	static int dummy_obj_size;
	void foward();
	void rotate(float angle);
	bool collision(bool map[ArrSize][ArrSize], int x, int y);
	bool wallCollision(int x, int y);
	bool enemyCollision();
	bool itemCollision(int x, int y);
};