#include <iostream> 
#include <vector>
#include <glm/mat4x4.hpp>
#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include <glm/gtc/matrix_transform.hpp>
#include "objloader.hpp"
#include "shader.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <cmath>
#define CellSize 200

GLuint programID;
GLuint ProjectionID;
GLuint ViewID;
GLuint ModelID;
GLuint ColorID;
GLuint VertexArrayID;
glm::mat4 MVP;
GLuint vertexbuffer;
unsigned int dummy_obj_size;
bool third_person_view = false;

//Player player(0.0f,0.0f);
using namespace std; 

glm::mat4 cameraMove() {
	float dx=0.0f;//offset for the point looked at
	float dy=0.0f;
	float dhx = 0.0f;//offset for head position
	float dhy = 0.0f;
	float dtx = 0.0f;
	float dty = 0.0f;//offset for third-person view
	float dtz = 0.0f;
	if (third_person_view)
		dtz = 400.0f;
	else
		dtz = 0.0f;

	if (Player::player.direction == 0.0f) {
		dx = 1000.0f;
		dy = 0.0f;
		dhx = 20.0f;
		dhy = 0.0f;
		if (third_person_view) {
			dtx = -1000.0f;
			dty = 0.0f;
		}
		else {
			dtx = dty = 0.0f;
		}
	}
	else if (Player::player.direction == 90.0f) {
		dx = 0.0f;
		dy = 1000.0f;
		dhx = 0.0f;
		dhy = 20.0f;
		if (third_person_view) {
			dtx = 0.0f;
			dty = -1000.0f;
		}
		else {
			dtx = dty = 0.0f;
		}
	}
	else if (Player::player.direction == 180.0f) {
		dx = -1000.0f;
		dy = 0.0f;
		dhx = -20.0f;
		dhy = 0.0f;
		if (third_person_view) {
			dtx = 1000.0f;
			dty = 0.0f;
		}
		else {
			dtx = dty = 0.0f;
		}
	}
	else if (Player::player.direction == 270.0f) {
		dx = 0.0f;
		dy = -1000.0f;
		dhx = 0.0f;
		dhy = -20.0f;
		if (third_person_view) {
			dtx = 0.0f;
			dty = 1000.0f;
		}
		else {
			dtx = dty = 0.0f;
		}
	}
	return glm::lookAt(glm::vec3(Player::player.x+dhx+dtx, Player::player.y+dhy+dty, 170.0f+dtz),
		glm::vec3(Player::player.x+dx, Player::player.y+dy, 169.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
}
void display() {
	
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
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
	float angle;
	switch (key) {
	case 'w':
		Player::player.foward();
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
	Player::player = Player(50*200, 50*200);
	Enemy::initMap();
	Wall::initMap();
	
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