#ifndef TRAPS_H
#define TRAPS_H
#pragma once

#include <vector>
#include <raylib.h>

#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"

#include "Map.h"

class Trap {
public:
	Trap(Math::ivec2 index) ;
	void Load();
	void Update(double dt);
	void Draw();
	void Unload();
	bool& SetIsAlive() { return is_alive; }
	const bool& GetIsAlive() const { return is_alive; }
	Rectangle& SetTrapRect() { return trap_rect; }
	const Rectangle& GetTrapRect() const { return trap_rect; }
	

private:
	
	CS230::Sprite sprite_trap_dead;
	CS230::Sprite sprite_trap_alive;
	Math::ivec2 index;
	Rectangle trap_rect;
	
	bool is_alive = true;
	/*const double trap_max_count = 1.0;
	double trap_count = 1.0;*/
};

#endif // !TRAPS_H

