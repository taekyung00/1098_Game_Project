#include "Bishop.h"

Bishop::Bishop(Math::ivec2 index) :
	Enemy(index) {
	AddGOComponent(new CS230::Sprite("Assets/Bishop.spt", this));
	ReachableIndexPush();
	//ChangeMapDesign();
}

//void Bishop::Update([[maybe_unused]] double dt) {
//	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
//	if ((is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
//		ReachableIndexPush();
//		ChangeIndex();
//		ReachableIndexPush();
//		ChangeMapDesign();
//		SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
//		is_outdated = false;
//		Engine::GetLogger().LogDebug("Bishop is updated");
//	}
//	if ((is_outdated == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
//		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space)) {
//			turn_manager->Sub();
//			++(turn_manager->SetCurrentTurn());
//			is_outdated = true;
//
//		}
//	}
//}

void Bishop::ReachableIndexPush() {
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	reachable_indices.clear();

	Math::ivec2 temp_index = GetIndex();
	while ((map->GetTileDesign()[temp_index.x][temp_index.y].isLeftEdge == false) && (map->GetTileDesign()[temp_index.x][temp_index.y].isTopEdge == false))
	{
		temp_index.x--;
		temp_index.y++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while ((map->GetTileDesign()[temp_index.x][temp_index.y].isRightEdge == false) && (map->GetTileDesign()[temp_index.x][temp_index.y].isTopEdge == false))
	{
		temp_index.x++;
		temp_index.y++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while ((map->GetTileDesign()[temp_index.x][temp_index.y].isLeftEdge == false) && (map->GetTileDesign()[temp_index.x][temp_index.y].isBottomEdge == false))
	{
		temp_index.x--;
		temp_index.y--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while ((map->GetTileDesign()[temp_index.x][temp_index.y].isRightEdge == false) && (map->GetTileDesign()[temp_index.x][temp_index.y].isBottomEdge == false))
	{
		temp_index.x++;
		temp_index.y--;
		reachable_indices.push_back(temp_index);
	}
}