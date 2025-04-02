#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "Map.h"

#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"

class Enemy;
class Player {
public:

	Player(Map& map);
	void Load();
	void Update(double dt, const Enemy& enemy);
	void Draw();
	void Unload();
	Math::ivec2 GetIndex() const { return index; }
	Math::ivec2 GetPosition() const { return player_position; }
	double GetTimeLimit() const { return time_limit; }

private:
	Map& map;
	//CS230::Camera& camera;



	Math::ivec2 index_start;
	Math::ivec2 index;
	Math::ivec2 player_position;

	int radius;

	int moving_count;
	double time_limit = 3;
	bool is_moving;

};
#endif // !PLAYER_H