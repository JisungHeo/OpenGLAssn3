#pragma once
//#include <iostream> 
#include <vector>
#include <glm/mat4x4.hpp>
#include <GL/glew.h> 
//#include <glm/glm.hpp>
#include <GL/freeglut.h> 
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
#include "gamemanager.hpp"
#include <cmath>
#include "texture.hpp"
#include <iostream>
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
GLuint TextureID;
GLuint TextureExistID;
GLuint VertexArrayID;
GLuint vertexbuffer;
unsigned int dummy_obj_size;
bool third_person_view = false;
int time_timer=0;
int enemy_timer=0;
int bullet_speed =10;

//static Player player; //= Player(50 * 200 + 100, 50 * 200 + 100);
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
	glUniform3fv(glGetUniformLocation(programID, "viewPos"), 1, &glm::vec3(Player::player.x + dhx + dtx, Player::player.y + dhy + dty, 170.0f + dtz)[0]);
	return glm::lookAt(glm::vec3(Player::player.x+dhx+dtx, Player::player.y+dhy+dty, 170.0f+dtz),
		glm::vec3(Player::player.x+dx, Player::player.y+dy, 169.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
}

void drawEntity() {
	Player::player.draw();
	Wall::drawAll();
	Enemy::drawAll();
	Item::drawAll();
	Bullet::drawAll();
	drawStatusBar();
}

void display() {
	if (!GameManager::game_over) { // if game is not over.
		
		glViewport(0, 0.2*height, width, 0.8*height);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		glUseProgram(programID);
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 3000.0f);
		glm::mat4 View = cameraMove();
		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Projection[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);

		//dir light
		glUniform4f(ColorID, 0.0f, 1.0f, 0.0f, 1.0f);
		glUniform4f(glGetUniformLocation(programID, "lightColor"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(programID, "dirLight.direction"), -1.0f, -1.0f, -1.0f);
		glUniform3f(glGetUniformLocation(programID, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(programID, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(programID, "dirLight.specular"), 1.0f, 1.0f, 1.0f);
		
		//points light
		glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), PI / 180 * Player::player.direction, glm::vec3(0, 0, 1));
		float light_x = (float)Player::player.x;
		float light_y = (float)Player::player.y;
		float light_z = 0.0f;
		//cout << "x:" << light_x << " ,y=" << light_y << endl;
		//glm::vec4 point_0 =  glm::vec4(10000.0f, 10000.0f, light_z, 1.0f);
		glm::vec4 point_0= rotateMatrix * glm::vec4(light_x, light_y, light_z,1.0f);
		glm::vec4 point_1 = rotateMatrix * glm::vec4(light_x , light_y, light_z, 1.0f);
		glm::vec4 offset = rotateMatrix * glm::vec4(200,100,60,0);
		//glUniformMatrix4fv(glGetUniformLocation(programID, "rotateMatrix"), 1, GL_FALSE, &rotateMatrix[0][0]);
		glUniform3f(glGetUniformLocation(programID, "pointLights[0].position"), light_x + offset[0], light_y + offset[1], light_z + offset[2]);
		glUniform3f(glGetUniformLocation(programID, "pointLights[0].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(programID, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(programID, "pointLights[0].specular"), 1.0f, 1.0f,1.0f);
		glUniform1f(glGetUniformLocation(programID, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(programID, "pointLights[0].linear"), 0.0009);
		glUniform1f(glGetUniformLocation(programID, "pointLights[0].quadratic"), 0.0000032);
		
		offset = rotateMatrix * glm::vec4(200, -100, 60, 0);
		glUniform3f(glGetUniformLocation(programID, "pointLights[1].position"), light_x + offset[0], light_y + offset[1], light_z + offset[2]);
		glUniform3f(glGetUniformLocation(programID, "pointLights[1].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(programID, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(programID, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(programID, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(programID, "pointLights[1].linear"), 0.0009);
		glUniform1f(glGetUniformLocation(programID, "pointLights[1].quadratic"), 0.0000032);
		
		drawEntity();
		glutSwapBuffers();
	}
	else {
			glViewport(0, 0.2*height, width, 0.8*height);
			glutSwapBuffers();
			printtext(210, 60, "Game Over");
			printtext(180, 50, "Prees 'r' for Retry");
	}
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
	case 'r':
		if (GameManager::game_over) {
			GameManager::game_over = false;
			GameManager::map_clear();
			GameManager::gameStatusInit();
			GameManager::game_round += 1;
		}
	}
	glutPostRedisplay();
}



void update(int time) {
	if (!GameManager::game_over) {
		Bullet::update();
		Item::update();
		Enemy::update();
		GameManager::timeUpdate();
		//GameManager::lifeUpdate();
	}
	GameManager::checkGameOver();
	glutTimerFunc(50, update, time++);
	glutPostRedisplay();
}

void init() {
	//shader
	programID = LoadShaders("myVS.glsl", "myFS.glsl");
	
	ProjectionID = glGetUniformLocation(programID, "Projection");
	ViewID = glGetUniformLocation(programID, "View");
	ModelID = glGetUniformLocation(programID, "Model");
	ColorID = glGetUniformLocation(programID, "fragmentColor");
	TextureID = glGetUniformLocation(programID, "myTextureSampler");
	TextureExistID = glGetUniformLocation(programID, "textureExist");
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

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (Player::player.doing == false) {
			Player::player.bulletLoad();
			Player::vertexArrayID = Player::vertexArrayIDs[9];
			Player::player.doing = true;
		}
	}
	else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		Player::vertexArrayID = Player::vertexArrayIDs[0];
		Player::player.doing = false;
	}
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
	glutMouseFunc(mouse);
	//glutTimerFunc(0, timer, 0);
	glutTimerFunc(10, update, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glewInit();
	init();
	glutMainLoop(); 
}