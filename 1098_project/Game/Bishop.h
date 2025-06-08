#pragma once
#include "Enemy.h"

class Bishop : public Enemy {
public:
	Bishop(Math::ivec2 index);
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
	void ReachableIndexPush() override;
	void ResolveCollision(GameObject* other_object) override;
private:
	CS230::Sprite movable;
	const int max_turn_count = 1;
	int current_turn = 1;
};
