#include "enemy.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "objloader.hpp"
#include "player.hpp"
#include "map.hpp"

#define CellSize 200
#define ArrSize 100
#define PI 3.141592f
///using namespace std;

extern GLuint ModelID;
extern GLuint ColorID;
extern bool map_enemy[ArrSize][ArrSize];
extern bool map_wall[ArrSize][ArrSize];
extern bool map_bullet[ArrSize][ArrSize];
vector<Enemy> Enemy::vectorEnemy;

Enemy::Enemy(float x, float y) {
	this->x = x;
	this->y = y;
}

GLuint Enemy::vertexArrayID;
int Enemy::dummy_obj_size;
void Enemy::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x,y, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(1, 0, 0));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < dummy_obj_size / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
}
/*
void Enemy::draw2() {
	initVertices();
	GLuint vertexbuffer;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer 
	);

	MVP = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f) *
		glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
<<<<<<< HEAD
		//scale     	//glm::scale(glm::mat4(1.0f), glm::vec3(30.0f));
	//glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
}*/

void Enemy::initVAO() {
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("obj_files/dummy_obj_red.obj", vertices, uvs, normals);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer 
	);
	dummy_obj_size = vertices.size();
}


void Enemy::initVertices() {
	bool res = loadOBJ3("obj_files/Skeleton.obj", vertices, uvs);
}

void Enemy::initMap() {
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) {
			map_enemy[i*25+5][j*25+5] = 1;
			//map_enemy[i * 25 + 5][j * 25 + 19] = 1;
			//map_enemy[i * 25 + 19][j * 25 + 5] = 1;
			map_enemy[i * 25 + 19][j * 25 + 19] = 1;
			//map_enemy[i * 25 + 12][j * 25 + 12] = 1;
		}
	for (int i = 0; i < ArrSize; i++)
		for (int j = 0; j < ArrSize; j++)
			if(map_enemy[i][j])
				Enemy::vectorEnemy.push_back(Enemy(i*CellSize, j*CellSize));
}
void Enemy::drawAll() {
	for (int i = 0; i < vectorEnemy.size(); i++)
		vectorEnemy[i].draw();
}

bool Enemy::wallCollision(int x, int y)
{
	return map_wall[x][y] == 1;
}

bool Enemy::bulletCollision(int x, int y) {
	return map_bullet[x][y] == 1;
}