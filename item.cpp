#include "item.hpp"
#include "objloader.hpp"
#include <cmath>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "map.hpp"
#include "player.hpp"
#define PI 3.14159
extern GLuint ModelID;
extern GLuint ColorID;
extern bool map_item[ArrSize][ArrSize];
GLuint Item::vertexArrayID;
int Item::verticesSize;
vector<Item> Item::vectorItem;

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
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(30.0f));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 0.0f, 0.0f, 1.0f, 1.0f);
	for (int i = 0; i < verticesSize / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
}

bool Item::playerCollision(int x, int y) {
	return map_item[x][y] != 0;
}

void Item::update() {
	int fit_x = int(Player::player.x / 200);
	int fit_y = int(Player::player.y / 200);
	for (int i = 0; i <vectorItem.size(); i++) {
		if (vectorItem[i].playerCollision(fit_x,fit_y)) {
			int type = vectorItem[i].type;
			Player::player.itemlist[type] = true;
			map_item[fit_x][fit_y] = 0;
			vectorItem[i].~Item();
			vectorItem.erase(vectorItem.begin() + i);
		}
	}
}


void Item::initMap() {
	map_item[50][49] = 1;
	//map_item[50][46] = 1;
	int half = CellSize / 2;
	vectorItem.push_back(Item(0, 50 * CellSize +half, 49 * CellSize+half));
	//vectorItem.push_back(Item(1, 50 * CellSize + half, 46 * CellSize+half));
}
void Item::drawAll() {
	for (int i = 0; i < vectorItem.size(); i++)
		vectorItem[i].draw();
}