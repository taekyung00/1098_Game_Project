#pragma once
#include "Enemy.h"
#include "../Engine/Timer.h"
#include "Player.h"

class King : public Enemy {
public:
	King(Math::ivec2 index);
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
	GameObjectTypes Type() override { return GameObjectTypes::King; }
	std::string TypeName() override { return "King"; }
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
	//const int max_turn_count = 1;
	//int current_turn = 0;
	int life = 3;
	void attack() override;
	CS230::Timer* turn_timer;
	static constexpr double turn_time = 1.0;
};