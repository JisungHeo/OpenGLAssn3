#include "gun.hpp"
#include "objloader.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//glm::mat4 MVP;
extern GLuint ModelID;
GLuint Gun::VertexArrayID;
int Gun::dummy_obj_size;

Gun::Gun(float x, float y)
{
	this->x = x;
	this->y = y;
}


void Gun::draw() {
	glBindVertexArray(VertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
		/*scale*/glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));

	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	for (int i = 0; i < dummy_obj_size / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
}

void Gun::initVAO() {
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	bool res = loadOBJ("obj_files/M1911.obj", vertices, uvs, normals);
	dummy_obj_size = vertices.size();

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
