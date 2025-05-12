#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include "Player.h"
#include "Enemy.h"
class CollisionManager {
public:
	CollisionManager(Player& player, std::vector<Enemy*>& enemies);
	void CollisionCheck();
private:
	Player& player;
	std::vector<Enemy*>& enemies;
};
#endif // !COLLISIONMANAGER_H


