#pragma once
#include "Enemy.h"

class Arrow : public Enemy {
public:
	Arrow(Math::ivec2 start_index, Math::ivec2 dest_index);
	GameObjectTypes Type() override { return GameObjectTypes::Arrow; }
	std::string TypeName() override { return "Arrow"; }
	void Update(double dt) override;
	void ReachableIndexPush() override {};
	void ResolveCollision(GameObject* other_object) override;
private:
	Math::ivec2 start_index;
	Math::ivec2 dest_index;
	//Math::vec2 temp_pos;
};