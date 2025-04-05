#ifndef ENEMY_H
#define ENEMY_H

#pragma once

#include <cstdlib>
#include <ctime>

#include "../Engine/Vec2.h"
#include "Map.h"
#include "Player.h"

class Enemy {
public:
	struct attackarm;

	Enemy(Map& map, Player& player);
	void Load();
	void Update(double dt, bool& isEnemyTurn, bool& isPlayerTurn);
	void Draw();
	void Unload();
	Math::ivec2 GetIndex() const { return index; }
	const std::vector<attackarm>& GetArms() const { return attackarms; }

private:
	Map& map;
	Player& player;

	Math::ivec2 index_start;
	Math::ivec2 index;

	Math::ivec2 position;

	bool is_attacking;
	double attcak_count;

	double enemy_turn_count = 3;

	struct attackarm {
		Vector2 center;
		int radius;
	};

	std::vector<attackarm> attackarms;
	//bool is_moving;

};

#endif // !ENEMY_H


