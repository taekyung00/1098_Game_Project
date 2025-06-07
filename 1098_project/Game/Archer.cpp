#include "Archer.h"
#include "Player.h"

Archer::Archer(Math::ivec2 index) : 
	Enemy(index),
	movable("Assets/Movable.spt", this),
	arrow(nullptr)
{
	AddGOComponent(new CS230::Sprite("Assets/Archer.spt", this));
	ReachableIndexPush();
}

void Archer::Update(double dt) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {

		if (current_turn == 0) {
			current_turn = max_turn_count;
			
			make_arrow();
		}
		else {
			ReachableIndexPush();
			destroy_arrow();
			--current_turn;
		}

		//SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
		is_outdated = false;
		Engine::GetLogger().LogDebug("Enemy is updated");
	}
	if ((is_outdated == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space)) {
			is_outdated = true;
		}
	}
}

void Archer::ReachableIndexPush() {
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	Math::ivec2 player_index = player->GetIndex();
	reachable_indices.clear();
	reachable_indices.push_back(player_index);
}

void Archer::make_arrow()
{
	CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
	destroy_arrow();
	arrow = new Arrow(reachable_indices[0]);
	gameobjectmanager->Add(arrow);
}

void Archer::destroy_arrow()
{
	if (arrow != nullptr) {
		arrow->Destroy();
		arrow = nullptr;
	}
	
}

void Archer::Draw(Math::TransformationMatrix camera_matrix) {
	GameObject::Draw(camera_matrix);
	if (current_turn == 0) {
		movable.Draw(camera_matrix * GetMatrix());
	}
}
