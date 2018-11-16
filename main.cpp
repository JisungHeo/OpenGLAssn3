#pragma once
//#include <iostream> 
#include <vector>
#include <glm/mat4x4.hpp>
#include <GL/glew.h> 
//#include <glm/glm.hpp>
//#include <GL/freeglut.h> 
#include <glm/gtc/matrix_transform.hpp>
#include "objloader.hpp"
#include "shader.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "item.hpp"
#include "gun.hpp"
#include "bullet.hpp"
#include "statusbar.hpp"
#include <cmath>
#define CellSize 200
#define PI 3.141592f
using namespace std;

int width;
int height;
GLuint programID;
GLuint ProjectionID;
GLuint ViewID;
GLuint ModelID;
GLuint ColorID;
GLuint VertexArrayID;
GLuint vertexbuffer;
unsigned int dummy_obj_size;
bool third_person_view = false;

//Player player(0.0f,0.0f);

glm::mat4 cameraMove() {
	float dx=0.0f;//offset for the point looked at
	float dy=0.0f;
	float dhx = 0.0f;//offset for head position
	float dhy = 0.0f;
	float dtx = 0.0f;
	float dty = 0.0f;//offset for third-person view
	float dtz = 0.0f;
	glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), PI/180*Player::player.direction, glm::vec3(0, 0, 1));
	glm::vec4 thirdVector = rotateMatrix * glm::vec4(-1000.0f, 0.0f, 400.0f, 1.0f);
	glm::vec4 headVector = rotateMatrix * glm::vec4(20.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 atVector = rotateMatrix * glm::vec4(1000.0f, 0.0f, 0.0f,1.0f);
	if (third_person_view) {
		dtx = thirdVector.x;
		dty = thirdVector.y;
		dtz = thirdVector.z;
	}
	else
		dtx = dty = dtz = 0.0f;
	dhx = headVector.x;
	dhy = headVector.y;
	dx = atVector.x;
	dy = atVector.y;
	return glm::lookAt(glm::vec3(Player::player.x+dhx+dtx, Player::player.y+dhy+dty, 170.0f+dtz),
		glm::vec3(Player::player.x+dx, Player::player.y+dy, 169.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
}
void display() {
	glViewport(0, 0.2*height, width, 0.8*height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programID);
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10000.0f);
	glm::mat4 View = cameraMove();
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Projection[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
	
	glUniform4f(ColorID, 0.0f, 1.0f, 0.0f, 1.0f);
	Player::player.draw();
	Enemy enemy(200.0f,0.0f);
	enemy.draw();
	Wall::drawAll();
	Enemy::drawAll();
	Item::drawAll();
	Gun gun(50*CellSize, 49*CellSize);
	gun.draw();
	Bullet bullet(0, 50 * CellSize, 48 * CellSize);
	bullet.draw();
	drawStatusBar();
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0.2*h, w, h*0.8);
	width = w;
	height = h;

}

void keyboard(unsigned char key, int x, int y) {
	float angle;
	switch (key) {
	case 'w':
		Player::player.
		Player::player.forward();
		break;

	case 'a':
		Player::player.rotate(90.0f);
		break;

	case 'd':
		Player::player.rotate(-90.0f);
		break;

	case 'q':
		third_person_view = !third_person_view;
		break;
	}
	printf("%f\n", Player::player.direction);
	glutPostRedisplay();
}

void timer(int time) {
	time++;
}
void init() {
	//shader
	programID = LoadShaders("myVS.glsl", "myFS.glsl");
	
	ProjectionID = glGetUniformLocation(programID, "Projection");
	ViewID = glGetUniformLocation(programID, "View");
	ModelID = glGetUniformLocation(programID, "Model");
	ColorID = glGetUniformLocation(programID, "fragmentColor");
	
	Player::initVAO();
	Enemy::initVAO();
	Wall::initVAO();
	Item::initVAO();
	Gun::initVAO();
	Bullet::initVAO();
	Player::player = Player(50*200 + 100, 50*200 + 100);
	Enemy::initMap();
	Wall::initMap();
	Item::initMap();
	glutSwapBuffers();
}
void main(int argc, char **argv) {  	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(700, 700); 
	glutCreateWindow("Hello OpenGL"); 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, timer, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glewInit();
	init();
	glutMainLoop(); 
}