#include "player.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "objloader.hpp"
#include <GL/glut.h>
#define ArrSize 100
#define CellSize 200
#define PI 3.141592f
#define NUM_FRAME 8
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
	this->doing = false;
}

GLuint Player::vertexArrayID;
GLuint Player::vertexArrayIDs[9] = { 0 };
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
	char path[100];
	for (int i=0; i < NUM_FRAME+1; i++) {
		vector<glm::vec3> vertices;
		vector<glm::vec2> uvs;
		vector<glm::vec3> normals; // Won't be used at the moment.
		if (i == 0)
			sprintf(path, "obj_files/dummy_obj.obj");
		else
			sprintf(path, "obj_files/dummy_obj_%d.obj", i);
		bool res = loadOBJ(path, vertices, uvs, normals);

		glGenVertexArrays(1, &vertexArrayIDs[i]);
		glBindVertexArray(vertexArrayIDs[i]);

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
	vertexArrayID = vertexArrayIDs[0];
}


void forward_step(int value) {
	if (Player::player.direction == 0.0f)
		Player::player.x += CellSize / 8;
	else if (Player::player.direction == 90.0f)
		Player::player.y += CellSize / 8;
	else if (Player::player.direction == 180.0f)
		Player::player.x -= CellSize / 8;
	else if (Player::player.direction == 270.0f)
		Player::player.y -= CellSize / 8;
	Player::vertexArrayID = Player::vertexArrayIDs[NUM_FRAME - value];

	if (value > 0)
		glutTimerFunc(50, forward_step, value - 1);
	else {
		Player::vertexArrayID = Player::vertexArrayIDs[0];
		Player::player.doing = false;
	}
	glutPostRedisplay();
}

void Player::forward() {
	float prev_x = x;
	float prev_y = y;
	if (direction == 0.0f)
		prev_x+= CellSize;
	else if (direction == 90.0f)
		prev_y += CellSize;
	else if (direction == 180.0f)
		prev_x -= CellSize;
	else if (direction == 270.0f)
		prev_y -= CellSize;
	if (!wallCollision(prev_x/200, prev_y/200))
	{
		printf("wall is not here");
		if (doing == false) {
			glutTimerFunc(0, forward_step, NUM_FRAME - 1);
			doing = true;
		}
	}
}

void rotate_step(int value) {
	float angle;
	if (value / 8)
		angle = 90.0f;
	else
		angle = -90.0f;
	Player::player.direction = fmod(Player::player.direction + angle/NUM_FRAME, 360.0f);
	if (Player::player.direction < 0)
		Player::player.direction += 360.0f;
	if (value %8 > 0)
		glutTimerFunc(50, rotate_step, value - 1);
	else
		Player::player.doing = false;
	glutPostRedisplay();
}

void Player::rotate(float angle) {
	int dir = angle == 90.0f;
	if (doing == false) {
		glutTimerFunc(0, rotate_step, dir*8+NUM_FRAME - 1);
		doing = true;
	}
}

bool Player::collision(bool map[ArrSize][ArrSize], int x, int y) {
	return map[x][y] == 1;
	/*bool upCollision = map[x / 50][(y + 25) / 50] == 1;
	bool downCollision = map[x / 50][(y - 25) / 50] == 1;
	bool leftCollision = map[(x - 25) / 50][y / 50] == 1;
	bool rightCollision = map[(x + 25) / 50][y / 50] == 1;
	return upCollision || downCollision || leftCollision || rightCollision;*/
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
