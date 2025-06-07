#pragma once

#include "Enemy.h"

class CannonBall : public Enemy {
public:
	CannonBall(Math::ivec2 index);
	GameObjectTypes Type() override { return GameObjectTypes::CannonBall; }
	std::string TypeName() override { return "CannonBall"; }
	void ReachableIndexPush() override {};

};
