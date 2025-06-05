#pragma once
#include "Enemy.h"

class Pawn : public Enemy {
public:
	Pawn(Math::ivec2 index);
	
    void ReachableIndexPush() override;
};
