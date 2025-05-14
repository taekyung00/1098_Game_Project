#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Trap.h"
class CollisionManager {
public:
	CollisionManager(Map& map,Player& player, std::vector<Enemy*>& enemies, std::vector<Trap*>& traps);
	void CollisionCheck();
private:
	Map& map;
	Player& player;
	std::vector<Enemy*>& enemies;
	std::vector<Trap*>& traps;
};
#endif // !COLLISIONMANAGER_H


