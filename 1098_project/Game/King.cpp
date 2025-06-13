#include "King.h"

King::King(Math::ivec2 index) : 
	Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/King.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	turn_timer = new CS230::Timer(0.0);
	AddGOComponent(turn_timer);
	ReachableIndexPush();
	SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
}

void King::Update([[maybe_unused]] double dt) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	//Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if (Destroyed() == true) {
		return;
	}
	switch (GetGOComponent<CS230::Sprite>()->CurrentAnimation())
	{
	case static_cast<int>(Animations::Idle):
		break;
	case static_cast<int>(Animations::Attacking):
		if (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
		}
		break;
	case static_cast<int>(Animations::Attackable):
		break;
	case static_cast<int>(Animations::Attacked):
		if (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
		}
		break;
	case static_cast<int>(Animations::Defeated):
		if (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true) {
			Destroy();
			Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->EraseEnemy(this);
		}
		break;
	}
	GameObject::Update(dt);
	if ((turn_ended == false) && (is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		//bool is_player_in_reachable = false;
		//for (Math::ivec2 _index : reachable_indices) {
		//	if (_index == player->GetIndex()) {
		//		is_player_in_reachable = true;
		//		break;
		//		//reachable_indices.erase(std::remove(reachable_indices.begin(), reachable_indices.end(), _index), reachable_indices.end());
		//	}
		//}
		//if (is_player_in_reachable == true) {
		//	attack();
		//}
		
		is_outdated = false;
		Engine::GetLogger().LogDebug("Enemy is updated");
		turn_timer->Set(turn_time);
	}
	if ((turn_ended == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (turn_timer->Remaining() == 0.0) {
			turn_ended = true;
			is_outdated = true;
		}
	}
}

void King::ReachableIndexPush() {
	reachable_indices.clear();

	reachable_indices.push_back({GetIndex().x-1,GetIndex().y});
	reachable_indices.push_back({GetIndex().x+1,GetIndex().y});
	reachable_indices.push_back({GetIndex().x,GetIndex().y-1});
	reachable_indices.push_back({GetIndex().x,GetIndex().y+1});
	reachable_indices.push_back(GetIndex());
}

void King::attack() {
	//TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	//Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	//if ((did_attack == false) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
	//	player->SetIndex() = { 2,0 };
	//	did_attack = true;
	//}
}

void King::Defeated()
{
	if (life > 0) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacked));
		--life;
	}
	if (life == 0) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Defeated));
	}
	
}

void King::Draw(Math::TransformationMatrix camera_matrix) {

	//if (current_turn == 0) {
	//	//GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
	//	movable.Draw(camera_matrix * GetMatrix());
	//}
	GameObject::Draw(camera_matrix);
}