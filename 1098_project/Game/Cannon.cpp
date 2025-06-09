#include "Cannon.h"
Cannon::Cannon(Math::ivec2 index) :
	Enemy(index),
	movable("Assets/Movable.spt", this)
{
	AddGOComponent(new CS230::Sprite("Assets/Cannon.spt", this));
	ReachableIndexPush();
	ChangeMapDesign();
}

void Cannon::Update([[maybe_unused]] double dt) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((turn_ended == false) && (is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {

		if (current_turn == 0) {
			current_turn = max_turn_count;
			ReachableIndexPush();
			
			make_cannonball();
		}
		else {
			destroy_cannonball();
			--current_turn;
		}

		//SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
		is_outdated = false;
		Engine::GetLogger().LogDebug("Enemy is updated");
	}
	if ((turn_ended == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space)) {
			turn_ended = true;
			is_outdated = true;
		}
	}
	ChangeMapDesign();
}

void Cannon::ReachableIndexPush() {
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	Math::ivec2 player_index = player->GetIndex();
	reachable_indices.clear();

	Math::ivec2 temp_index = GetIndex();

	std::vector<Math::ivec2>left_candidate_indices;
	std::vector<Math::ivec2>right_candidate_indices;
	std::vector<Math::ivec2>top_candidate_indices;
	std::vector<Math::ivec2>bottom_candidate_indices;

	while (map->GetTileDesign()[temp_index.x][temp_index.y].isLeftEdge == false)
	{
		temp_index.x--;
		left_candidate_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isRightEdge == false)
	{
		temp_index.x++;
		right_candidate_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isBottomEdge == false)
	{
		temp_index.y--;
		bottom_candidate_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isTopEdge == false)
	{
		temp_index.y++;
		top_candidate_indices.push_back(temp_index);
	}

	Math::ivec2 temp_idx = GetIndex();
	for (Math::ivec2 _index : left_candidate_indices) {
		if (Math::GetDistanceSquaredBetweenIndices(temp_idx, player_index) > Math::GetDistanceSquaredBetweenIndices(_index, player_index)) {
			temp_idx = _index;
		}
	}
	for (Math::ivec2 _index : right_candidate_indices) {
		if (Math::GetDistanceSquaredBetweenIndices(temp_idx, player_index) > Math::GetDistanceSquaredBetweenIndices(_index, player_index)) {
			temp_idx = _index;
		}
	}
	for (Math::ivec2 _index : bottom_candidate_indices) {
		if (Math::GetDistanceSquaredBetweenIndices(temp_idx, player_index) > Math::GetDistanceSquaredBetweenIndices(_index, player_index)) {
			temp_idx = _index;
		}
	}
	for (Math::ivec2 _index : top_candidate_indices) {
		if (Math::GetDistanceSquaredBetweenIndices(temp_idx, player_index) > Math::GetDistanceSquaredBetweenIndices(_index, player_index)) {
			temp_idx = _index;
		}
	}

	if (std::find(left_candidate_indices.begin(), left_candidate_indices.end(), temp_idx) != left_candidate_indices.end()) {
		reachable_indices = left_candidate_indices;
	}
	else if (std::find(right_candidate_indices.begin(), right_candidate_indices.end(), temp_idx) != right_candidate_indices.end()) {
		reachable_indices = right_candidate_indices;
	}
	else if (std::find(bottom_candidate_indices.begin(), bottom_candidate_indices.end(), temp_idx) != bottom_candidate_indices.end()) {
		reachable_indices = bottom_candidate_indices;
	}
	else if (std::find(top_candidate_indices.begin(), top_candidate_indices.end(), temp_idx) != top_candidate_indices.end()) {
		reachable_indices = top_candidate_indices;
	}
}

void Cannon::make_cannonball()
{
	if (did_attack == false) {
		CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
		destroy_cannonball();
		for (Math::ivec2 _index : reachable_indices) {
			CannonBall* new_cannonball = new CannonBall(_index);
			cannonballs.push_back(new_cannonball);
			gameobjectmanager->Add(new_cannonball);
		}
		did_attack = true;
	}
	
}

void Cannon::destroy_cannonball()
{
	for (CannonBall* cannonball : cannonballs) {
		cannonball->Destroy();
	}
	cannonballs.clear();
}

void Cannon::Draw(Math::TransformationMatrix camera_matrix) {
	GameObject::Draw(camera_matrix);
	if (current_turn == 0) {
		movable.Draw(camera_matrix * GetMatrix());
	}
}

//void Cannon::ResolveCollision(GameObject* other_object) {
//
//}