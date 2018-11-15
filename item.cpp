#include "item.hpp"
#include "objloader.hpp"
#include <cmath>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.14159
extern GLuint ModelID;
extern GLuint ColorID;
extern map_item
GLuint Item::vertexArrayID;
static int verticesSize;


Item::Item(int type, float x, float y)
{
	this->type = type;
	this->x = x;
	this->y = y;
}

void Item::initVAO() {
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	bool res = loadOBJ3("obj_files/item.obj", vertices, uvs);
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	GLuint vertexbuffer;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
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
	verticesSize = vertices.size();
}


void Item::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f) *
		glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(30.0f));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	
	glBindVertexArray(0);
}

bool Item::playerCollision()
{
	//**thinking point
	return false;
	//return (this->x == player.x) && (this->y == player.y);
}

void Item::initMap() {
	
}
void Item::drawAll();