#pragma once
#include "Enemy.h"

class Trap : public Enemy {
public:
	Trap(Math::ivec2 index);
	void ReachableIndexPush() override {};
private:
	CS230::Sprite* alive_sprite;
	CS230::Sprite* dead_sprite;
};
