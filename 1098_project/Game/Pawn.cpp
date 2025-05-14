#include "Pawn.h"
#include "InGame.h"


Pawn::Pawn(Math::ivec2 index, std::string sprite_path) : 
	Enemy(index, sprite_path) {
	sprite.Load(sprite_path.c_str(),{0,0});
	
	
}
void Pawn::Load()
{
	rect = { static_cast<float>(position.x),static_cast<float>(position.y),static_cast<float>(tile_size.x),static_cast<float>(tile_size.y) };
	ReachableTest();
}
void Pawn::Update([[maybe_unused]]double dt)
{
	if (is_outdated == true) {
		near_index.clear();
		ReachableTest();
		ChangeIndex();
		UpdateNearIndex();
		ReachableTest();
		position =
			Math::vec2{ static_cast<double>(start_position.x), static_cast<double>(start_position.y) } +
			Math::vec2{ static_cast<double>(current_index.y * tile_size.y), static_cast<double>(current_index.x * tile_size.x) };
		//rect = { 0.f, 0.f, static_cast<float>(tile_size.x), static_cast<float>(tile_size.y) };
		is_outdated = false;
		rect = { static_cast<float>(position.x),static_cast<float>(position.y),static_cast<float>(tile_size.x),static_cast<float>(tile_size.y) };
	}
	
	
}

void Pawn::ReachableTest()
{
	/*for (Math::ivec2 index : reachable_indices) {
		map->SetTileDesign()[index.x][index.y].isPawnReachable = false;
	}*/

	/*for (int i = 0; i < map->GetTileDesign().size(); ++i) {
		for (int j = 0; j < map->GetTileDesign()[i].size(); ++j) {
			map->SetTileDesign()[i][j].isPawnReachable = false;
		}
	}*/
	for (Math::ivec2 index : reachable_indices) {
		map->SetTileDesign()[index.x][index.y].isPawnReachable = false;
		//distances_between_enemy_player[index] = GetDistanceBetweenIndices(index, player->GetCurrentIndex());
	}

	reachable_indices.clear();
	distances_between_enemy_player.clear();

	Math::ivec2 temp_index = current_index;
	if (map->GetTileDesign()[current_index.x][current_index.y ].isLeftEdge == false) {
		temp_index.y--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = current_index;
	if (map->GetTileDesign()[current_index.x][current_index.y ].isRightEdge == false) {
		temp_index.y++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = current_index;
	if (map->GetTileDesign()[current_index.x ][current_index.y].isBottomEdge == false) {
		temp_index.x++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = current_index;
	if (map->GetTileDesign()[current_index.x ][current_index.y ].isTopEdge == false) {
		temp_index.x--;
		reachable_indices.push_back(temp_index);
	}

	for (Math::ivec2 index : reachable_indices) {
		map->SetTileDesign()[index.x][index.y].isPawnReachable = true;
		distances_between_enemy_player[index] = GetDistanceBetweenIndices(index,player->GetCurrentIndex());
	}
}

Pawn::~Pawn()
{
	reachable_indices.clear();
	distances_between_enemy_player.clear();
	for (int i = 0; i < map->GetTileDesign().size(); ++i) {
		for (int j = 0; j < map->GetTileDesign()[i].size(); ++j) {
			map->SetTileDesign()[i][j].isPawnReachable = false;
		}
	}
}





