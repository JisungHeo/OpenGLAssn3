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
GLuint programID;
GLuint ProjectionID;
GLuint ViewID;
GLuint ModelID;
GLuint ColorID;
GLuint VertexArrayID;
glm::mat4 MVP;
GLuint vertexbuffer;
unsigned int dummy_obj_size;


//Player player(0.0f,0.0f);
using namespace std; 
void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programID);
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10000.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 10000.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Projection[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
	glUniform4f(ColorID, 0.0f, 1.0f, 0.0f, 1.0f);
	Player player(0.0f, 0.0f);
	player.draw();
	Enemy enemy(200.0f,0.0f);
	enemy.draw();
	Wall::drawAll();
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		break;

	case 'a':
		break;

	case 'd':
		break;
	}
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