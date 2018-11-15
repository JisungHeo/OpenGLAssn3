#include "enemy.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "player.hpp"
#define CellSize 200
#define ArrSize 100
#define PI 3.141592f
extern bool map_enemy[ArrSize][ArrSize];
extern GLuint ModelID;
extern GLuint ColorID;
vector<Enemy> Enemy::vectorEnemy;
Enemy::Enemy(float x, float y) {
	this->x = x;
	this->y = y;
	Enemy::vertexArrayID = Player::vertexArrayID;
	printf("%d", Enemy::vertexArrayID);
}

GLuint Enemy::vertexArrayID;
int Enemy::dummy_obj_size;
void Enemy::draw() {
	glBindVertexArray(vertexArrayID);
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(x,y, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), PI / 180 * 90.0f, glm::vec3(1, 0, 0));// glm::mat4(1.0f);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniform4f(ColorID, 1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < Player::dummy_obj_size / 4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
}
void Enemy::initVAO() {
	Enemy::vertexArrayID = Player::vertexArrayID;
	Enemy::dummy_obj_size = Player::dummy_obj_size;
}

void Enemy::initMap() {
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) {
			map_enemy[i*25+5][j*25+5] = 1;
			map_enemy[i * 25 + 5][j * 25 + 19] = 1;
			map_enemy[i * 25 + 19][j * 25 + 5] = 1;
			map_enemy[i * 25 + 19][j * 25 + 19] = 1;
			map_enemy[i * 25 + 12][j * 25 + 12] = 1;
		}
	for (int i = 0; i < ArrSize; i++)
		for (int j = 0; j < ArrSize; j++)
			if(map_enemy[i][j])
				Enemy::vectorEnemy.push_back(Enemy(i*CellSize, j*CellSize));
}
void Enemy::drawAll() {
	for (int i = 0; i < vectorEnemy.size(); i++)
		vectorEnemy[i].draw();
}