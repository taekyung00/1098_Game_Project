#pragma once
#include "Enemy.h"

class Bishop : public Enemy {
public:
	Bishop(Math::ivec2 index);
	//void Update(double dt) override;
	void ReachableIndexPush() override;
};
