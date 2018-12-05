#include "wall.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "texture.hpp"
#include <iostream>
using namespace std;
#define CellSize 200
#define ArrSize 100

extern bool map_wall[ArrSize][ArrSize];
extern GLuint ModelID;
extern GLuint ColorID;
extern GLuint TextureID;
extern GLuint TextureExistID;
extern GLuint programID;
vector<Wall> Wall::vectorWall;
Wall::Wall(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

glm::vec3 Wall::vertices[8] = { glm::vec3(0,0,0),glm::vec3(200,0,0),glm::vec3(200,200,0),glm::vec3(0,200,0),
		 glm::vec3(0,0,200),glm::vec3(200,0,200),glm::vec3(200,200,200),glm::vec3(0,200,200) };

GLuint Wall::vertexArrayID = 0;

int Wall::indices[24] = {
	0,1,2,3,
	1,2,6,5,
	4,5,6,7,
	3,0,4,7,
	0,1,5,4,
	2,3,7,6
};

GLfloat Wall::uv[48] = {
	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,

	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,

	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,

	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,

	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,

	0.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f,
};

GLfloat Wall::normals[72] = {
	0.0f,0.0f,-1.0f, 0.0f,0.0f,-1.0f, 0.0f,0.0f,-1.0f, 0.0f,0.0f,-1.0f,
	1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,0.0f,1.0f,
	-1.0f,0.0f,0.0f, -1.0f,0.0f,0.0f, -1.0f,0.0f,0.0f, -1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f, 0.0f,-1.0f,0.0f, 0.0f,-1.0f,0.0f, 0.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f
};

glm::vec3 Wall::out_vertices[24];
GLuint Wall::Texture;

void Wall::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model;
	Model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 0.0f, 0.0f, 0.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Wall::Texture);
	glUniform1i(TextureID, 0);
	glUniform1i(TextureExistID, 1);
	glUniform1i(glGetUniformLocation(programID, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(programID, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(programID, "material.shininess"), 32.0f);
	for (int i = 0; i < 24 / 4; i++) {
		glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);
	}
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	glUniform1i(TextureExistID, 0);
	//glBindVertexArray(0);
}


void Wall::initVAO() {
	glGenVertexArrays(1, &Wall::vertexArrayID);
	glBindVertexArray(Wall::vertexArrayID);
	for (int i = 0; i < 24; i++)
		out_vertices[i] = vertices[indices[i]];
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	Wall::Texture = loadDDS("diffuse.DDS");
	

}

void horizontalWall(int i, int j, int n) {
	for (int k = 0; k < n; k++)
		map_wall[i][j + k] = 1;
}

void verticalWall(int i, int j, int n) {
	for (int k = 0; k < n; k++)
		map_wall[i + k][j] = 1;
}

void Wall::initMap() {
	for (int i = 0; i < ArrSize; i++) {
		map_wall[i][0] = map_wall[0][i] = map_wall[i][ArrSize-1] = map_wall[ArrSize-1][i] = 1;
	}
	for (int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) {
			horizontalWall(i * 25 + 9, j * 25 + 3, 7);
			horizontalWall(i * 25 + 9, j * 25 + 15, 7);
			horizontalWall(i * 25 + 15, j * 25 + 3, 7);
			horizontalWall(i * 25 + 15, j * 25 + 15, 7);
			verticalWall(i * 25 + 3, j * 25 + 9, 7);
			verticalWall(i * 25 + 3, j * 25 + 15, 7);
			verticalWall(i * 25 + 15, j * 25 + 9, 7);
			verticalWall(i * 25 + 15, j * 25 + 15, 7);
		}
	map_wall[50][53] = 1;
	for (int i = 0; i < ArrSize; i++)
		for (int j = 0; j < ArrSize; j++) {
			if (map_wall[i][j])
				Wall::vectorWall.push_back(Wall(i*CellSize, j*CellSize, 0 * CellSize));
			//Ground
			Wall::vectorWall.push_back(Wall(i*CellSize, j*CellSize, -1 * CellSize));
		}
}

void Wall::drawAll() {
	for (int i = 0; i < vectorWall.size(); i++)
		vectorWall[i].draw();
}
