#pragma once
#include <vector>
#include "../Engine/Vec2.h"
#include "../Engine/GameObjectManager.h"
#include "Enemy.h"
#include "Player.h"
#include "CannonBall.h"

class Cannon : public Enemy {
public:
	Cannon(Math::ivec2 index);
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
	void ReachableIndexPush() override;
	//void ResolveCollision(GameObject* other_object) override;
private:
	CS230::Sprite movable;
	const int max_turn_count = 2;
	int current_turn = 0;
	std::vector<CannonBall*>cannonballs;
	void make_cannonball();
	void destroy_cannonball();


};
