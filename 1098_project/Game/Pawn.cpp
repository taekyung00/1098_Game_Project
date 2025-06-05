#include "Pawn.h"
#include "Rook.h"

Pawn::Pawn(Math::ivec2 index) :
	Enemy(index) {
	AddGOComponent(new CS230::Sprite("Assets/Pawn.spt", this));
	ReachableIndexPush();
	//ChangeMapDesign();
}




void Pawn::ReachableIndexPush()
{
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	reachable_indices.clear();

	Math::ivec2 temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isLeftEdge == false) {
		temp_index.x--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isRightEdge == false) {
		temp_index.x++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isBottomEdge == false) {
		temp_index.y--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isTopEdge == false) {
		temp_index.y++;
		reachable_indices.push_back(temp_index);
	}
}