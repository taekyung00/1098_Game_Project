#pragma once
#include "../Engine/Timer.h"
#include "Enemy.h"
#include "Arrow.h"
class Archer : public Enemy {
public:
	Archer(Math::ivec2 index);
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
	void ReachableIndexPush() override;
	//void ResolveCollision(GameObject* other_object) override;
	enum class Animations {
		Idle,
		Attacking,
		Attackable,
		Attacked,
		Defeated
	};
	void Defeated() override;
private:
	//CS230::Sprite movable;
	const int max_turn_count = 2;
	int current_turn = 2;
	//Arrow* arrow;
	void make_arrow();
	//void destroy_arrow();
	CS230::Timer* turn_timer;
	static constexpr double turn_time = 1.5;
};
