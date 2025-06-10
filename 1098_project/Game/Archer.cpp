#include "Archer.h"
#include "Player.h"

Archer::Archer(Math::ivec2 index) : 
	Enemy(index),
	movable("Assets/Movable.spt", this),
	arrow(nullptr)
{
	AddGOComponent(new CS230::Sprite("Assets/Archer.spt", this));
	ReachableIndexPush();
	ChangeMapDesign();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Archer::Update([[maybe_unused]]double dt) {
	GameObject::Update(dt);
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacked)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Defeated));
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Defeated)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->EraseEnemy(this);
		Destroy();
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacking)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		if (current_turn == 0) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
		}
		else {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
		}
	}
	if ((turn_ended == false) && (is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {

		if (current_turn == 0) {
			current_turn = max_turn_count;
			
			make_arrow();
		}
		else {
			ReachableIndexPush();
			
			destroy_arrow();
			--current_turn;
		}
		if (current_turn == 0) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
		}
		else {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
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

void Archer::ReachableIndexPush() {
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	Math::ivec2 player_index = player->GetIndex();
	reachable_indices.clear();
	reachable_indices.push_back(player_index);
}

void Archer::make_arrow()
{
	if (did_attack == false) {
		CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
		destroy_arrow();
		arrow = new Arrow(GetIndex(), reachable_indices[0]);
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
		gameobjectmanager->Add(arrow);
		did_attack = true;
	}
	
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
void Archer::Defeated()
{
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacked));
}
//void Archer::ResolveCollision(GameObject* other_object) {
//
//}