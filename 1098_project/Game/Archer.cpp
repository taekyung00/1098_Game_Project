#include "Archer.h"
#include "Player.h"

Archer::Archer(Math::ivec2 index) : 
	Enemy(index,{scale_const.x,scale_const.y/1.5})
	//movable("Assets/Movable.spt", this),
	//arrow(nullptr)
{
	AddGOComponent(new CS230::Sprite("Assets/Archer.spt", this));
	ReachableIndexPush();
	ChangeMapDesign();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	turn_timer = new CS230::Timer(0.0);
	AddGOComponent(turn_timer);
	arrow_attack_ptr = new Audio("Assets/Sounds/Arrow_ef.mp3");
	arrow_attack_ptr->SetLooping(false);
	AddGOComponent(arrow_attack_ptr);
}

void Archer::Update([[maybe_unused]]double dt) {
	if (Destroyed() == true) {
		return;
	}
	arrow_attack_ptr->Update();
	GameObject::Update(dt);
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacked)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Defeated));
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Defeated))) {
		if ((GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
			Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->EraseEnemy(this);
			Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(GetIndex());
			Destroy();
		}
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
			
			//destroy_arrow();
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
		turn_timer->Set(turn_time);
	}
	if ((turn_ended == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (turn_timer->Remaining() == 0.0) {
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
		//destroy_arrow();
		//arrow = ;
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
		arrow_attack_ptr->Play();
		gameobjectmanager->Add(new Arrow(GetIndex(), reachable_indices[0]));
		did_attack = true;
	}
	
}

//void Archer::destroy_arrow()
//{
//	if (arrow != nullptr) {
//		arrow->Destroy();
//		arrow = nullptr;
//	}
//	
//}

void Archer::Draw(Math::TransformationMatrix camera_matrix) {
	GameObject::Draw(camera_matrix);
	//if (current_turn == 0) {
	//	movable.Draw(camera_matrix * GetMatrix());
	//}
}

void Archer::Defeated()
{
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacked));
}