#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "Map.h"
#include "../Engine/Vec2.h"

class Player {
public:

	Player(Map& map);
	void Load();
	void Update();
	void Draw();
	void Unload();
	Math::ivec2 GetIndex() { return index; }

private:
	Map& map;

	Math::ivec2 index_start;
	Math::ivec2 index;

	int moving_count;
	bool is_moving;

};
#endif // !PLAYER_H