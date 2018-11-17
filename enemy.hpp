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
	bool isWallThere(int);
	bool isNearPlayer(int, int); 
	int getDirectionWithNoWall();
	int getPlayerPartition(int, int);
	int getDirectionToMove();
	static void update();

	static vector<Enemy> vectorEnemy;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	GLuint VertexArrayID;
	float x;
	float y;
	static GLuint vertexArrayID;
	static int dummy_obj_size;
};

enum direction { UP, DOWN, RIGHT, LEFT };