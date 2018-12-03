#include "gamemanager.hpp"
#include <iostream>
#include "enemy.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "map.hpp"
#include "item.hpp"
#include "wall.hpp"

using namespace std;
int GameManager::game_round=1;
int GameManager::life=4;
int GameManager::time=150;
int GameManager::game_over=0;
bool GameManager::game_over_txt = true;

extern int time_timer,enemy_timer,bullet_speed;
extern bool map_enemy[ArrSize][ArrSize];
extern bool map_wall[ArrSize][ArrSize];
extern bool map_bullet[ArrSize][ArrSize];
extern bool map_item[ArrSize][ArrSize];
GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::timeUpdate() {
	if (time_timer > 30) {
		time--;
		time_timer = 0;
	}
	time_timer += 1;
}

//Return if game is over
void GameManager::checkGameOver() {
	if (life == 0) {
		game_over = true;
	}
	else if (Enemy::vectorEnemy.empty()) {
		game_over = true;
	}
	else if (time == 0) {
		game_over = true;
	}
}

void GameManager::lifeUpdate() {
	if (Player::player.prev_collision == 0 && Player::player.enemyCollision()) {
		life--;
		Player::player.prev_collision == 1;
	}
	Player::player.prev_collision = Player::player.enemyCollision();
	return;
}

void GameManager::map_clear() {
	//Item
	for (int i = 0; i < Item::vectorItem.size(); i++) {
		Item::vectorItem[i].~Item();
		Item::vectorItem.erase(Item::vectorItem.begin() + i);
	}

	//Enemy
	for (int i = 0; i < Enemy::vectorEnemy.size(); i++) {
		Enemy::vectorEnemy[i].~Enemy();
		Enemy::vectorEnemy.erase(Enemy::vectorEnemy.begin() + i);
	}
	//Bullet
	for (int i = 0; i < Bullet::vectorBullet.size(); i++) {
		Bullet::vectorBullet[i].~Bullet();
		Bullet::vectorBullet.erase(Bullet::vectorBullet.begin() + i);
	}
	for (int i = 0; i < Wall::vectorWall.size(); i++) {
		Wall::vectorWall[i].~Wall();
		Wall::vectorWall.erase(Wall::vectorWall .begin() + i);
	}
	Item::vectorItem.clear();
	Enemy::vectorEnemy.clear();
	Bullet::vectorBullet.clear();
	Wall::vectorWall.clear();
	//map_data clear;
	int i, j;
	for (i = 0; i < ArrSize; i++) {
		for (j = 0; j < ArrSize; j++) {
			map_enemy[i][j] = 0;
			map_bullet[i][j] = 0;
			map_item[i][j] = 0;
			map_wall[i][j] = 0;
		}
	}
}

void GameManager::gameStatusInit() {
	Enemy::initMap();
	Wall::initMap();
	Item::initMap();
	Player::player.x = 50 * CellSize + CellSize / 2;
	Player::player.y = 50 * CellSize + CellSize / 2;
	Player::player.itemlist[0] = false;
	Player::player.itemlist[1] = false;
	life = 4;
	time = 150;
	bullet_speed = 4;
	game_over = false;
	enemy_timer = 0;
	time_timer = 0;
	glutSwapBuffers();
}