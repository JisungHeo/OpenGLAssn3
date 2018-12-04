#include "enemy.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "objloader.hpp"
#include "player.hpp"
#include "map.hpp"
#include "gamemanager.hpp"
#include "texture.hpp"
#define CellSize 200
#define ArrSize 100
#define PI 3.141592f
#define NUM_FRAME 8
///using namespace std;

//Player player = Player(50 * 200 + 100, 50 * 200 + 100);
extern GLuint ModelID;
extern GLuint ColorID;
extern GLuint TextureID;
extern GLuint TextureExistID;
extern bool map_enemy[ArrSize][ArrSize];
extern bool map_wall[ArrSize][ArrSize];
extern bool map_bullet[ArrSize][ArrSize];
vector<Enemy> Enemy::vectorEnemy;

extern int enemy_timer;
extern int bullet_speed;
GLuint Enemy::vertexArrayIDs[9];


Enemy::Enemy(float x, float y) {
	this->x = x;
	this->y = y;
	this->action = 0;
	this->frame = 0;
}

GLuint Enemy::vertexArrayID;
int Enemy::dummy_obj_size;
GLuint Enemy::Texture;
void Enemy::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x,y, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * direction, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(1, 0, 0));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 1.0f, 0.0f, 0.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Enemy::Texture);
	glUniform1i(TextureID, 0);
	glUniform1i(TextureExistID, 1);
	for (int i = 0; i < dummy_obj_size / 4; i++) {
		glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
	}
	glUniform1i(TextureExistID, 0);
	glBindVertexArray(0);
}
/*
void Enemy::draw2() {
	initVertices();
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

	MVP = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f) *
		glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
<<<<<<< HEAD
		//scale     	//glm::scale(glm::mat4(1.0f), glm::vec3(30.0f));
	//glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
}*/

void Enemy::initVAO() {
	vertexArrayID = Player::vertexArrayID;
	for (int i=0;i<9;i++)
		vertexArrayIDs[i] = Player::vertexArrayIDs[i];
	dummy_obj_size = Player::dummy_obj_size;
	Enemy::Texture = loadDDS("obj_files/dummy_red.dds");
	/*vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("obj_files/dummy_obj_red.obj", vertices, uvs, normals);

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
	dummy_obj_size = vertices.size();*/

}


void Enemy::initVertices() {
	bool res = loadOBJ3("obj_files/Skeleton.obj", vertices, uvs);
}

void Enemy::initMap() {
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) {
			map_enemy[i*25+5][j*25+5] = 1;
			//map_enemy[i * 25 + 5][j * 25 + 19] = 1;
			//map_enemy[i * 25 + 19][j * 25 + 5] = 1;
			map_enemy[i * 25 + 19][j * 25 + 19] = 1;
			//map_enemy[i * 25 + 12][j * 25 + 12] = 1;
		}
	for (int i = 0; i < ArrSize; i++)
		for (int j = 0; j < ArrSize; j++)
			if(map_enemy[i][j])
				Enemy::vectorEnemy.push_back(Enemy(i*CellSize+CellSize/2, j*CellSize+CellSize/2));
}
bool isVisible(Enemy enemy) {
	if (abs(enemy.x / CellSize - Player::player.x / CellSize) < 15 && abs(enemy.x / CellSize - Player::player.x / CellSize) < 15)
		return true;
	else
		return false;
}
void Enemy::drawAll() {
	for (int i = 0; i < vectorEnemy.size(); i++)
		if(isVisible(vectorEnemy[i]))
			vectorEnemy[i].draw();
}

bool Enemy::wallCollision(int x, int y)
{
	return map_wall[x][y] == 1;
}

bool Enemy::bulletCollision() {
	return map_bullet[int(x/200)][int(y/200)] == 1;
}

void Enemy::move()
{
	float prev_x = x;
	float prev_y = y;
	float direction = getDirectionToMove();
	if (direction == 90.0f)
		y += CellSize;
	else if (direction ==270.0f)
		y -= CellSize;
	else if (direction == 0.0f)
		x += CellSize;
	else if (direction == 180.0f)
		x -= CellSize;
	
	map_enemy[int(prev_x/200)][int(prev_y/200)] = 0;
	map_enemy[int(x/200)][int(y/200)] = 1;
}

void Enemy::move_step()
{
	float prev_x = x;
	float prev_y = y;
	if (action == 0) {
		direction = getDirectionToMove();
		action = 1;
		frame = 8;
	}
	if (action == 1) {
		if (direction == 90.0f)
			y += CellSize / NUM_FRAME;
		else if (direction == 270.0f)
			y -= CellSize / NUM_FRAME;
		else if (direction == 0.0f)
			x += CellSize / NUM_FRAME;
		else if (direction == 180.0f)
			x -= CellSize / NUM_FRAME;

		map_enemy[int(prev_x / 200)][int(prev_y / 200)] = 0;
		map_enemy[int(x / 200)][int(y / 200)] = 1;
		vertexArrayID = vertexArrayIDs[NUM_FRAME+1 - frame];
	}

	frame--;
	if (frame == 0)
		action = 0;
}

bool Enemy::isNearPlayer(int dist_x, int dist_y)
{
	if (abs(dist_x/200) <= 5 && abs(dist_y/200) <= 5) {//in close region
		return true;
	}
	return false;
}
int Enemy::getPlayerPartition(int dist_x, int dist_y)
{
	//UP, DOWN, RIGHT, LEFT
	int partition;
	if (dist_y < 0) {//1,2
		if (dist_x < 0) {//1 - UP, RIGHT
			partition = 1;
		}
		else {//2 - UP, LEFT
			partition = 2;
			if (dist_x == 0) partition = 5;
		}
	}
	else if (dist_y == 0) {//6,8
		if (dist_x > 0) partition = 6;
		else partition = 8;
	}
	else {//3,4
		if (dist_x > 0) {//3-DOWN, LEFT
			partition = 3;
		}
		else {//4-DOWN,RIGHT
			partition = 4;
			if (dist_x == 0) partition = 7;
		}
	}
	return partition;
}

bool Enemy::isWallThere(float direction) {//check if there is wall in certain direction
	int new_x = this->x;
	int new_y = this->y;
	if (direction == 90.0f)
		new_y += CellSize;
	else if (direction == 270.0f)
		new_y -= CellSize;
	else if(direction == 180.0f)
		new_x-=CellSize;
	else if(direction == 0.0f)
		new_x+=CellSize;
	return wallCollision(new_x/200, new_y/200);
}

int Enemy::getDirectionToMove()//return Direction according to partition
{
	int dist_x, dist_y, partition, direction;
	dist_x = this->x - Player::player.x;
	dist_y = this->y - Player::player.y;
	if (!isNearPlayer(dist_x, dist_y)) {//far from player
		direction = getDirectionWithNoWall();
	}
	else {//near player
		partition = getPlayerPartition(dist_x, dist_y);
		//UP, DOWN, RIGHT, LEFT
		switch (partition) {
		case 1://up, right
			direction = 90.0f;
			if (isWallThere(direction))
				direction = 0.0f;
			break;
		case 2://up, left
			direction = 180.0f;
			if (isWallThere(direction))
				direction = 90.0f;
			break;
		case 3://down, left
			direction = 270.0f;
			if (isWallThere(direction))
				direction = 180.0f;
			break;
		case 4://down, right
			direction = 0.0f;
			if (isWallThere(direction))
				direction = 270.0f;
			break;
		case 5:
			direction = 90.0f; break;
		case 6:
			direction = 180.0f; break;
		case 7:
			direction = 270.0f; break;
		case 8:
			direction = 0.0f; break;
		}
		//if there are walls everywhere
		if (isWallThere(direction))
			direction = getDirectionWithNoWall();
	}
	return direction;
}

float Enemy::getDirectionWithNoWall() //Return direction with no Wall
{
	int dir;
	float directions[4] = { 90.0f,270.0f,180.0f,0.0f };
	do {
		dir = rand() % 4;
	} while (isWallThere(directions[dir]));
	return directions[dir];

}

void Enemy::update() {
	for (int i = 0; i < vectorEnemy.size(); i++) {
		if (vectorEnemy[i].bulletCollision()) {
			int x_tmp = int(vectorEnemy[i].x / 200);
			int y_tmp = int(vectorEnemy[i].y / 200);
			map_enemy[x_tmp][y_tmp] = 0;
			vectorEnemy[i].~Enemy();
			vectorEnemy.erase(vectorEnemy.begin() + i);
		}
	}
	for (int i = 0; i < vectorEnemy.size(); i++) {
		vectorEnemy[i].move_step();
	}
	glutPostRedisplay();
}