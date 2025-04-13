#ifndef ENEMY_H
#define ENEMY_H

#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../Engine/Vec2.h"
#include "Map.h"
#include "Player.h"
#include "TurnManager.h"

class Enemy {
public:
	struct attackarm;

	Enemy(TurnManager& turnmanager, Map& map, Player& player);
	void Load();
	void Update(double dt, bool& isEnemyTurn, bool& isPlayerTurn);
	void Draw();
	void Unload();
	void Attack();
	Math::ivec2 GetIndex() const { return index; }
	const std::vector<attackarm>& GetArms() const { return attackarms; }

private:
	TurnManager& turnmanager;
	Map& map;
	Player& player;

	Math::ivec2 index_start;
	Math::ivec2 index;

	Math::ivec2 position;

	bool is_attacking;
	double attcak_count;


	struct attackarm {
		Vector2 center;
		int radius;
	};

	std::vector<attackarm> attackarms;
	bool is_alive = true;

};

#endif // !ENEMY_H


