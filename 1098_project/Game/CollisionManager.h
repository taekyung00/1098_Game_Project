#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Trap.h"
class CollisionManager {
public:
	CollisionManager(Player& player, std::vector<Enemy*>& enemies, std::vector<Trap*>& traps);
	void CollisionCheck();
private:
	Player& player;
	std::vector<Enemy*>& enemies;
	std::vector<Trap*>& traps;
};
#endif // !COLLISIONMANAGER_H


