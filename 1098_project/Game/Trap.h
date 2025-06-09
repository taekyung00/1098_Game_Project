#pragma once
#include "States.h"
#include "Enemy.h"

class Trap : public Enemy {
public:
	Trap(Math::ivec2 index);
	void ReachableIndexPush() override {};
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
	GameObjectTypes Type() override { return GameObjectTypes::Trap; }
	std::string TypeName() override { return "Trap"; }
	//int DrawPriority() const override { return 2; }
	bool CanCollideWith(GameObjectTypes other_object_type) override;
	void ResolveCollision(GameObject* other_object) override;
private:
	CS230::Sprite* alive_sprite;
	CS230::Sprite* dead_sprite;
	CS230::Sprite* movable;
	const int max_turn_count = 2;
	int current_turn = 0;
	bool is_alive = true;
	//bool map_changed = true;
};
