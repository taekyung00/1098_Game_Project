#pragma once
#include "Enemy.h"

class Pawn : public Enemy {
public:
	Pawn(Math::ivec2 index);
	void Draw(Math::TransformationMatrix camera_matrix) override;
	void Update(double dt) override;
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
	CS230::Sprite movable;
	void attack() override;

};
