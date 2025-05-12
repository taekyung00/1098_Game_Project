#include "Pawn.h"
#include "InGame.h"


Pawn::Pawn(Math::ivec2 index, std::string sprite_path) : 
	Enemy(index), sprite_path(sprite_path) {
	sprite.Load(sprite_path.c_str(),{0,0});
}
void Pawn::Update([[maybe_unused]]double dt)
{
	near_index.clear();
	if (is_outdated == true) {
		//temperary moving
		if (map->GetTileDesign()[current_index.x][current_index.y].isLeftEdge != true) {
			--current_index.y;
			is_outdated = false;

		}
		else if (map->GetTileDesign()[current_index.x][current_index.y].isRightEdge != true) {
			++current_index.y;
			is_outdated = false;

		}

		if (map->GetTileDesign()[current_index.x][current_index.y].isTopEdge != true) {
			--current_index.x;
			is_outdated = false;

		}
		else if (map->GetTileDesign()[current_index.x][current_index.y].isBotttomEdge != true) {
			++current_index.x;
			is_outdated = false;

		}
	}
	near_index.push_back({ current_index.x - 1,current_index.y });
	near_index.push_back({ current_index.x + 1,current_index.y });
	near_index.push_back({ current_index.x,current_index.y - 1 });
	near_index.push_back({ current_index.x,current_index.y + 1});
	position =
		Math::vec2{ static_cast<double>(start_position.x), static_cast<double>(start_position.y) } +
		Math::vec2{ static_cast<double>(current_index.y * tile_size.y), static_cast<double>(current_index.x * tile_size.x) };
	rect = { 0.f, 0.f, static_cast<float>(tile_size.x), static_cast<float>(tile_size.y) };
	
}


