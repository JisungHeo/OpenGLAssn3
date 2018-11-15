#include "gun.h"
#include "objloader.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//glm::mat4 MVP;
GLuint MVPID;

Gun::Gun()
{
}


void Gun::draw() {
	glm::mat4 MVP = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f) *
		glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f)) *
		/*scale*/glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
}

void Gun::initVAO() {
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
}
void Gun::initVertices() {
	bool res = loadOBJ("obj_files/gun.obj", vertices, uvs, normals);
}