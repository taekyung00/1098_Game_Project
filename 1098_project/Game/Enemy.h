#ifndef ENEMY_H
#define ENEMY_H

#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../Engine/Vec2.h"
#include "Map.h"

#include "TurnManager.h"

class Player;

class Enemy {
public:
	Enemy(Math::ivec2 index);
	//virtual void Load();
	virtual void Update(double dt);
	virtual void Draw();
	virtual void Unload();

	static void SetPlayerReference(Player& p);
	static void SetMapReference(Map& m);
	bool& SetIsOutdated() { return is_outdated; }
	const Math::ivec2& GetCurrentIndex() const { return current_index; }
	const Math::vec2& GetPosition() const{ return position; }
	const Rectangle& GetRect() const{ return rect; }
	const std::vector < Math::ivec2 >& GetNearIndex() const { return near_index; }
	std::vector < Math::ivec2 >& SetNearIndex()  { return near_index; }
protected:
	static Map* map;
	static Player* player;
	CS230::Sprite sprite;	
	Math::ivec2 current_index;
	std::vector < Math::ivec2 > near_index;
	Math::vec2 position;
	Rectangle rect;
	bool is_outdated = true;
private:

	
	
};
//class Enemy {
//public:
//	struct attackarm;
//
//	Enemy(TurnManager& turnmanager, Map& map, Player& player);
//	void Load();
//	void Update(double dt);
//	void Draw();
//	void Unload();
//	void Attack();
//	Math::ivec2 GetIndex() const { return index; }
//	const std::vector<attackarm>& GetArms() const { return attackarms; }
//	bool& GetIsAlive() { return is_alive; }
//
//private:
//	TurnManager& turnmanager;
//	Map& map;
//	Player& player;
//
//	Math::ivec2 index_start;
//	Math::ivec2 index;
//
//	Math::ivec2 position;
//
//	bool is_attacking;
//	double attcak_count;
//
//
//	struct attackarm {
//		Vector2 center;
//		int radius;
//	};
//
//	std::vector<attackarm> attackarms;
//	bool is_alive = true;
//
//};

#endif // !ENEMY_H


