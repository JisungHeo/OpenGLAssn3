#include "enemy.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "objloader.hpp"
#include "player.hpp"
#include "map.hpp"

#define CellSize 200
#define ArrSize 100
#define PI 3.141592f
///using namespace std;

//Player player = Player(50 * 200 + 100, 50 * 200 + 100);
extern GLuint ModelID;
extern GLuint ColorID;
extern bool map_enemy[ArrSize][ArrSize];
extern bool map_wall[ArrSize][ArrSize];
extern bool map_bullet[ArrSize][ArrSize];
vector<Enemy> Enemy::vectorEnemy;

Enemy::Enemy(float x, float y) {
	this->x = x;
	this->y = y;
}

GLuint Enemy::vertexArrayID;
int Enemy::dummy_obj_size;
void Enemy::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x,y, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(1, 0, 0));
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < dummy_obj_size / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
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
	vector<glm::vec3> vertices;
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
	dummy_obj_size = vertices.size();
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
void Enemy::drawAll() {
	for (int i = 0; i < vectorEnemy.size(); i++)
		vectorEnemy[i].draw();
}

bool Enemy::wallCollision(int x, int y)
{
	//if (map_wall[x][y])
		//printf("wall collision");
	return map_wall[x][y] == 1;
}

bool Enemy::bulletCollision() {
	//printf("x = %f, y = %f", x, y);
	return map_bullet[int(x/200)][int(y/200)] == 1;
}

void Enemy::move()
{
	float prev_x = x;
	float prev_y = y;
	int direction = getDirectionToMove();
	if (direction == UP)
		y += CellSize;
	else if (direction ==DOWN)
		y -= CellSize;
	else if (direction == RIGHT)
		x += CellSize;
	else if (direction == LEFT)
		x -= CellSize;
	
	map_enemy[int(prev_x/200)][int(prev_y/200)] = 0;
	map_enemy[int(x/200)][int(y/200)] = 1;
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

bool Enemy::isWallThere(int direction) {//check if there is wall in certain direction
	int new_x = this->x;
	int new_y = this->y;
	switch (direction) {
	case UP: new_y+=CellSize; break;
	case DOWN: new_y-=CellSize; break;
	case RIGHT: new_x+=CellSize; break;
	case LEFT: new_x-=CellSize; break;
	}
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
			direction = UP;
			if (isWallThere(direction))
				direction = RIGHT;
			break;
		case 2://up, left
			direction = LEFT;
			if (isWallThere(direction))
				direction = UP;
			break;
		case 3://down, left
			direction = DOWN;
			if (isWallThere(direction))
				direction = LEFT;
			break;
		case 4://down, right
			direction = RIGHT;
			if (isWallThere(direction))
				direction = DOWN;
			break;
		case 5:
			direction = UP; break;
		case 6:
			direction = LEFT; break;
		case 7:
			direction = DOWN; break;
		case 8:
			direction = RIGHT; break;
		}
		//if there are walls everywhere
		if (isWallThere(direction))
			direction = getDirectionWithNoWall();
	}
	return direction;
}

int Enemy::getDirectionWithNoWall() //Return direction with no Wall
{
	int dir;
	do {
		dir = rand() % 4;
		//printf("dir : %d\n", dir);
	} while (isWallThere(dir));
	return dir;
}

void Enemy::update() {
	/*for (vector <Enemy>::iterator it = vectorEnemy.begin(); it != vectorEnemy.end();) {
		it->move();
	    if (it->bulletCollision()) {// when a bullet reached to wall, it disappears
			int x_tmp = ((*it).x) / 200;
			int y_tmp = ((*it).y) / 200;
			map_enemy[x_tmp][y_tmp] = 0;
			(*it).~Enemy();
			vectorEnemy.erase(i++);
		}
		else
			it++;
	}*/
	//int size = vectorEnemy.size();
	for (int i = 0; i < vectorEnemy.size(); i++) {
		vectorEnemy[i].move();
		if (vectorEnemy[i].bulletCollision()) {
			printf("bullet collision");
			vectorEnemy[i].~Enemy();
			vectorEnemy.erase(vectorEnemy.begin() + i);
			int x_tmp = int(vectorEnemy[i].x / 200);
			int y_tmp = int(vectorEnemy[i].y / 200);
			map_enemy[x_tmp][y_tmp] = 0;
			//vectorBullet[i].~Bullet();
		}
	}

	glutPostRedisplay();
}