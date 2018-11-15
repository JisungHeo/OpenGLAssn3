#include "wall.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "map.hpp"
extern GLuint ModelID;
extern GLuint ColorID;
vector<Wall> Wall::vectorWall;
Wall::Wall(float x, float y) {
	this->x = x;
	this->y = y;
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

glm::vec3 Wall::out_vertices[24];

void Wall::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model;
	Model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < 24 / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i*4, 4);
	}
	glBindVertexArray(0);
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
}

void Wall::initMap() {
	for (int i = 0; i < ArrSize; i++) {
		map_wall[i][0] = map_wall[0][i] = map_wall[i][ArrSize-1] = map_wall[ArrSize-1][i] = 1;
	}
	for (int i = 0; i < ArrSize; i++)
		for (int j = 0; j < ArrSize; j++)
			if (map_wall[i][j])
				Wall::vectorWall.push_back(Wall(i*CellSize, j*CellSize));
}

void Wall::drawAll() {
	for (int i = 0; i < vectorWall.size(); i++)
		vectorWall[i].draw();
}
