#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "bullet.hpp"
#define ArrSize 100
class Player {
public:
	Player(float x, float y);
	float x;
	float y;
	float direction;//degree x:0, y:90.0f, -x:180.0f, -y:270.0f
	static GLuint vertexArrayID;
	static GLuint vertexArrayIDs[10];
	void draw();
	static void initVAO();
	static Player player;
	static int dummy_obj_size;
	void forward();
	void rotate(float angle);
	void bulletLoad();
	bool itemCollision();
	bool collision(bool map[ArrSize][ArrSize], float x, float y);
	bool wallCollision(float, float);
	bool enemyCollision();
	bool doing;//to prevent multiple call at once.
	bool* itemlist;
};