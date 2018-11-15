#pragma once
#include "Bullet.h"
#include <cmath>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*#include "objloader.hpp"
#include "shader.hpp"
using namespace std;
glm::mat4 MVP;
GLuint MVPID;

Bullet::Bullet(int direction, float x, float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->direction = direction;
}

Bullet::~Bullet()
{
}

void Bullet::draw() {
	rotation(); 
	x_diff = 0;
	y_diff = 0; //move() function will be called outside **thinking point
	MVP =			glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f) *
						glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f)) *
	/*scale     */	//glm::scale(glm::mat4(1.0f), glm::vec3(30.0f))*
	/*rotation *///	glm::rotate(glm::mat4(1.0f), rotateAngle, glm::vec3(0.0f, 0.0f, 1.0f))*
	/*translate*/// glm::translate(glm::mat4(1.0), glm::vec3(x_diff, y_diff, 0));
	/*glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
}

void Bullet::initVertices() {
	//uvs, normal doesn't exist
	bool res = loadOBJ2("obj_files/bullet.obj", vertices);
}

void Bullet::initVAO() {
	GLuint vertexbuffer;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, NUM_FACES * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
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

/*
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
	int prev_x= this->x;
	int prev_y = this->y;

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
	x_diff = x - prev_x;
	y_diff = y - prev_y;
}

bool Bullet::wallCollision() {
	//collision check!!!
	//if (map_wall[x_fit][y_fit]) {//collision
		//map_bullet[x_fit][y_fit] = 0;
		//return true;
	//}
	return false;
}
*/