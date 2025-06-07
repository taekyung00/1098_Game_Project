#pragma once
#include "../Engine/Vec2.h"
struct Tile {
	int tile_number = 0;
	bool isRightEdge = false;
	bool isLeftEdge = false;
	bool isTopEdge = false;
	bool isBottomEdge = false;
	bool isUpStairs = false;
	bool isDownStairs = false;
	//bool isEnemyReachable = false;
};

const Math::ivec2 tile_size = { 32,32 };

const Math::vec2 start_position = { 200.0, 200.0 };

const Math::vec2 scale_const = { 2,2 };