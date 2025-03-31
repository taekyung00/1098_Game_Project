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

	Enemy(Map& map, Player& player);
	void Load();
	void Update();
	void Draw();
	void Unload();
	Math::ivec2 GetIndex() const { return index; }

private:
	Map& map;
	Player& player;

	Math::ivec2 index_start;
	Math::ivec2 index;

	//bool is_moving;

};

#endif // !ENEMY_H


