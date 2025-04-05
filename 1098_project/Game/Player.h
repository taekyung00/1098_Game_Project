#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "Map.h"
#include "FloorStateManager.h"

#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"

class Enemy;
class Player {
public:

	Player(Map& map, FloorStateManager& floorstatemanager);
	void Load();
	void Update(double dt, const Enemy& enemy);
	void Draw();
	void Unload();
	Math::ivec2 GetIndex() const { return index; }
	Math::ivec2 GetPosition() const { return player_position; }
	double GetTimeLimit() const { return time_limit; }

private:
	Map& map;
	FloorStateManager& floorstatemanager;

	//CS230::Camera& camera;



	Math::ivec2 index_start;
	Math::ivec2 index;
	Math::ivec2 player_position;

	int radius;

	int moving_count;
	double start_time_limit = 5;
	double max_time_limit = 2;
	double time_limit;
	bool is_moving;

};
#endif // !PLAYER_H