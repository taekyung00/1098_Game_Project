#include "Bishop.h"

Bishop::Bishop(Math::ivec2 index) :
	Enemy(index) ,
	movable("Assets/Movable.spt", this)
{
	AddGOComponent(new CS230::Sprite("Assets/Bishop.spt", this));
	ReachableIndexPush();
	ChangeMapDesign();
}

void Bishop::Update([[maybe_unused]] double dt) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		ReachableIndexPush();
		
		if (current_turn == 0) {
			current_turn = max_turn_count;
			ChangeIndex();
		}
		else {
			--current_turn;
		}

		ReachableIndexPush();
		
		//ChangeMapDesign();
		SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
		is_outdated = false;
		Engine::GetLogger().LogDebug("Enemy is updated");
	}
	if ((is_outdated == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space)) {
			is_outdated = true;
		}
	}
	ChangeMapDesign();
}

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

void Bishop::Draw(Math::TransformationMatrix camera_matrix) {
	GameObject::Draw(camera_matrix);
	if (current_turn == 0) {
		movable.Draw(camera_matrix * GetMatrix());
	}
}

void Bishop::attack() {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((did_attack == false)  && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(1);
		did_attack = true;
	}
}

