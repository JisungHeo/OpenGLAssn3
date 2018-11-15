#include "player.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "objloader.hpp"
#define ArrSize 100
#define CellSize 200
#define PI 3.141592f
using namespace std;
extern GLuint ModelID;
extern bool map_wall[ArrSize][ArrSize];
extern bool map_enemy[ArrSize][ArrSize];
extern bool map_item[ArrSize][ArrSize];
Player Player::player(0.0f,0.0f);
Player::Player(float x, float y) {
	this->x = x;
	this->y = y;
	this->direction = 90.0f;
}

GLuint Player::vertexArrayID;
int Player::dummy_obj_size;
void Player::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
		glm::rotate(glm::mat4(1.0f), PI / 180.0f * Player::player.direction, glm::vec3(0,0,1)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(1, 0, 0));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	for (int i = 0; i < dummy_obj_size / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
}
void Player::initVAO() {
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("obj_files/dummy_obj.obj", vertices, uvs, normals);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	GLuint vertexbuffer;
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
	dummy_obj_size = vertices.size();
}


void Player::foward() {
	if (Player::player.direction == 0.0f)
		Player::player.x += CellSize;
	else if (Player::player.direction == 90.0f)
		Player::player.y += CellSize;
	else if (Player::player.direction == 180.0f)
		Player::player.x -= CellSize;
	else if (Player::player.direction == 270.0f)
		Player::player.y -= CellSize;
}

void Player::rotate(float angle) {
	Player::player.direction = fmod(Player::player.direction + angle, 360.0f);
	if (Player::player.direction < 0)
		Player::player.direction += 360.0f;
}

bool Player::collision(bool map[ArrSize][ArrSize], int x, int y) {
	bool upCollision = map[x / 50][(y + 25) / 50] == 1;
	bool downCollision = map[x / 50][(y - 25) / 50] == 1;
	bool leftCollision = map[(x - 25) / 50][y / 50] == 1;
	bool rightCollision = map[(x + 25) / 50][y / 50] == 1;
	return upCollision || downCollision || leftCollision || rightCollision;
}
bool Player::wallCollision(int x, int y)
{
	return collision(map_wall, x, y);
}

bool Player::enemyCollision()
{
	return collision(map_enemy, x, y);
}

bool Player::itemCollision(int x, int y)
{
	return collision(map_item, x, y);
}
