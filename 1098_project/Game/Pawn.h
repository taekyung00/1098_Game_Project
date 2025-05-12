#ifndef PAWN_H
#define PAWN_H
#pragma once

#include"../Engine/Vec2.h"

#include "Enemy.h"

class Pawn : public Enemy {
public:
	Pawn(Math::ivec2 index, std::string sprite_path);
	void Update(double dt) override;
	
private:
	std::string sprite_path;
};
#endif // !PAWN_H


