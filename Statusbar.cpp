#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "statusbar.hpp"
using namespace std;
extern int width;
extern int height;

extern GLuint ColorID;
// function for printing text
// reference : http://programmingexamples.net/wiki/OpenGL/Text 
void printtext(int x, int y, string String)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	for (int i = 0; i<String.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glPopAttrib();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void writeItemInfo() {
	printtext(330, 80, "Item List");
	// when player got an item1
	printtext(330, 50, "three bullets");
	// when the player got item2
	printtext(330, 30, "speed up bullets");
}

void writeRoundInfo() {
	printtext(20, 80, "Round");
	printtext(20, 50, "game_round_s");
}

void writeTimerInfo() {
	printtext(110, 80, "Timer");
	printtext(110, 50, "time_s");
}

void writeLifeInfo() {
	printtext(200, 80, "Life");
	printtext(200, 50, "3");//life_s);
}

// function that draws a status bar below the screen
void drawStatusBar()
{
	glm::mat4 model_view;
	glm::mat4 projection;
	glViewport(0, 0, width, height / 5);
	projection = glm::ortho(0.0f, 500.0f, 0.0f, 100.0f);
	model_view = glm::mat4(1.0);
	glUniform4f(ColorID, 1.0f, 1.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 100);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();	
	glColor3f(0, 0, 0);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glUniform4f(ColorID, 0.3f, 0.3f, 0.3f, 1.0f);
	glColor3f(0.3, 0.3, 0.3);
	glUniform4f(ColorID, 0.0f, 0.0f, 0.0f, 0.0f);
	writeItemInfo();
	writeLifeInfo();
	writeTimerInfo();
	writeRoundInfo();
}
/*
void drawRect() {
	GLuint VertexArrayID;
	vector<glm::vec3> RectVertices = {
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 500.0, 0.0),
		glm::vec3(100.0, 0.0, 0.0),
		glm::vec3(100.0, 500.0, 0.0)
	};
	GLuint vertexbuffer;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, RectVertices.size() * sizeof(glm::vec3), &RectVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer 
	);

	glUniform4f(ColorID, 0.3f, 0.3f, 0.3f, 1.0f);
	MVP = glm::ortho(0.0f, 500.0f, 0.0f, 100.0f)*
			  glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
}*/