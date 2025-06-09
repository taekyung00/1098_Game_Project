#pragma once
#include "Enemy.h"

class Arrow : public Enemy {
public:
	Arrow(Math::ivec2 index);
	GameObjectTypes Type() override { return GameObjectTypes::Arrow; }
	std::string TypeName() override { return "Arrow"; }
	void ReachableIndexPush() override {};
	void ResolveCollision(GameObject* other_object) override;

};