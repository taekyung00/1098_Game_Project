#pragma once

#include "Enemy.h"

class CannonBall : public Enemy {
public:
	CannonBall(Math::ivec2 index);
	void ReachableIndexPush() override {};
};
