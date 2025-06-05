#pragma once
#include "Enemy.h"

class Rook : public Enemy {
public:
	Rook(Math::ivec2 index);
	//void Update(double dt) override;
	void ReachableIndexPush() override;
};
