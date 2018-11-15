#pragma once
#include "bullet.hpp"
#include <cmath>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "objloader.hpp"
#include "shader.hpp"
#include "map.hpp"
using namespace std;
extern bool map_bullet[ArrSize][ArrSize];
extern bool map_wall[ArrSize][ArrSize];
extern GLuint ModelID;
GLuint Bullet::VertexArrayID;
int Bullet::dummy_obj_size;

Bullet::Bullet(int direction, float x, float y)
{
	this->x = x;
	this->y = y;
	this->direction = direction;
}

Bullet::~Bullet()
{
}

void Bullet::draw() {
	rotation();
	glBindVertexArray(VertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0))*
		/*scale     */	glm::scale(glm::mat4(1.0f), glm::vec3(30.0f))*
		/*rotation */  glm::rotate(glm::mat4(1.0f), rotateAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		/*translate*/  

	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	for (int i = 0; i < dummy_obj_size / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
}


void Bullet::initVAO() {
	vector<glm::vec3> vertices;
	bool res = loadOBJ2("obj_files/bullet.obj", vertices);
	dummy_obj_size = vertices.size();

	GLuint vertexbuffer;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, dummy_obj_size * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer 
	);
}

/*back up
glm::mat4 Bullet::rotation() {
	switch (this->direction)
	{
	case 0: //UP
		return glRotatef(90, 0, 0, 1);
		break;
	case 1://DOWN
		glRotatef(-90, 0, 0, 1);
		break;
	case 2: //LEFT
		glRotatef(180, 0, 0, 1);
		break;
	default: //RIGHT
		break;
	}
}*/


void Bullet::rotation() {
	switch (this->direction)
	{
	case 0: //UP
		rotateAngle = 0.0f;
		break;
	case 1://DOWN
		rotateAngle = 180.0f;
		break;
	case 2: //LEFT
		rotateAngle = -90.0f;
		break;
	default: //RIGHT
		rotateAngle = -90.0f;
	}
}

void Bullet::move() {
	//0: up, 1:down, 2:left, 3:right
	int dir = this->direction;
	int prev_x_fit = this->x / 200;
	int prev_y_fit = this->y / 200;
	int x_fit, y_fit;

	if (dir == 0) {//up
		this->y = this->y + 1;
	}
	else if (dir == 1) {//down
		this->y = this->y - 1;
	}
	else if (dir == 2) {//left
		this->x = this->x - 1;
	}
	else {//right
		this->x = this->x + 1;
	}

	x_fit = this->x / 200;
	y_fit = this->y / 200;
	if ((x_fit != prev_x_fit )|| (y_fit!=prev_y_fit)) { //if there was any position change in block unit
		map_bullet[prev_x_fit][prev_y_fit] = 0;
		map_bullet[x_fit][y_fit] = 1;
	}
}

bool Bullet::wallCollision() {
	//collision check!!!
	int x_fit = this->x / 200;
	int y_fit = this->y / 200;
	if (map_wall[x_fit][y_fit]) {//collision
		map_bullet[x_fit][y_fit] = 0;
		return true;
	}
	return false;
}
