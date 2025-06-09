#pragma once
#include "Enemy.h"

class Pawn : public Enemy {
public:
	Pawn(Math::ivec2 index);
	void Draw(Math::TransformationMatrix camera_matrix) override;
    void ReachableIndexPush() override;
	void ResolveCollision(GameObject* other_object) override;
private:
	CS230::Sprite movable;

};
