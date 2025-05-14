#ifndef BISHOP_H
#define BISHOP_H
#pragma once

#include"../Engine/Vec2.h"

#include "Enemy.h"
class Bishop : public Enemy {
public:
	Bishop(Math::ivec2 index, std::string sprite_path);
	void Load() override;
	void Update(double dt) override;
	void ReachableTest() override;
	void ChangeMapDesign() override;
	~Bishop();
};

#endif // !BISHOP_H

