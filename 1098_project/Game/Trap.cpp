#include "Trap.h"
#include "InGame.h"





Trap::Trap(Math::ivec2 index)
	:index(index){
	
}

void Trap::Load()
{
	sprite_trap_alive.Load("Assets/sprite_trap_alive.png", { 0,0 });
	sprite_trap_dead.Load("Assets/sprite_trap_dead.png", { 0,0 });
	trap_rect = { static_cast<float>(start_position. x) + tile_size.x * index.y + 5, static_cast<float>(start_position.y) + tile_size.x * index.x + 5, static_cast<float>(tile_size.x) - 10,static_cast<float>(tile_size.y) - 10 };
	//trap_count = trap_max_count;
}

void Trap::Update([[maybe_unused]]double dt)
{
	is_alive = !is_alive;
	/*trap_count -= dt;
	if (trap_count <= 0.0) {
			    
	    trap_count = trap_max_count;
	}*/
}

void Trap::Draw()
{
	Math::vec2 position = Math::vec2{ static_cast<double>(start_position.x), static_cast<double>(start_position.y) } + Math::vec2{ static_cast<double>(index.y * tile_size.x), static_cast<double>(index.x * tile_size.y) };
	if (is_alive == true) {
		sprite_trap_alive.DrawRay(position);
	}
	else {
		sprite_trap_dead.DrawRay(position);
	}

}


