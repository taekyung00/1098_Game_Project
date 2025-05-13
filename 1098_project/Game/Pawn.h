#ifndef PAWN_H
#define PAWN_H
#pragma once

#include"../Engine/Vec2.h"

#include "Enemy.h"

class Pawn : public Enemy {
public:
	Pawn(Math::ivec2 index, std::string sprite_path);
	void Load() override;
	void Update(double dt) override;
	void ReachableTest() override;
	~Pawn();
	
private:
	std::string sprite_path;
};
#endif // !PAWN_H


