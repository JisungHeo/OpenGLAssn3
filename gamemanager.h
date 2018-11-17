#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();
	static int game_round;
	static int life;
	static int time;
	static int game_over;
	static bool game_over_txt;
	static void checkGameOver();
	static void timeUpdate();
	static void lifeUpdate();
	static void map_clear();
	static void gameStatusInit();
};

