#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
using namespace std;
class Enemy {
public:
	Enemy(float x, float y);
	void draw();
	//void draw2();
	void initVertices();
	static void initVAO();
	static void initMap();
	static void drawAll();
	bool wallCollision(int x, int y);
	bool bulletCollision();
	void move();
	//bool wallCollision(int, int);
	bool isWallThere(float);
	bool isNearPlayer(int, int); 
	float getDirectionWithNoWall();
	int getPlayerPartition(int, int);
	int getDirectionToMove();
	static void update();

	static vector<Enemy> vectorEnemy;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	GLuint VertexArrayID;
	static GLuint vertexArrayIDs[9];
	float x;
	float y;
	float direction;
	static GLuint vertexArrayID;
	static int dummy_obj_size;
	int action;//0: stationary, 1: forward, 2:rotate
	int frame;
	void move_step();
};

enum direction { UP, DOWN, RIGHT, LEFT };