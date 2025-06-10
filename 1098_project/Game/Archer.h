#pragma once
#include "Enemy.h"
#include "Arrow.h"
class Archer : public Enemy {
public:
	Archer(Math::ivec2 index);
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
	void ReachableIndexPush() override;
	//void ResolveCollision(GameObject* other_object) override;
private:
	CS230::Sprite movable;
	const int max_turn_count = 2;
	int current_turn = 2;
	Arrow* arrow;
	void make_arrow();
	void destroy_arrow();
};
