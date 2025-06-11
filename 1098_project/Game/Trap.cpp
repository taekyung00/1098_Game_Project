#include "InGame.h"
#include "Trap.h"
#include "Player.h"

Trap::Trap(Math::ivec2 index) : 
	Enemy(index),
	alive_sprite(new CS230::Sprite("Assets/TrapAlive.spt",this)),
	dead_sprite(new CS230::Sprite("Assets/TrapDead.spt",this))
	//movable(new CS230::Sprite("Assets/Movable.spt",this))

{
	AddGOComponent(alive_sprite);
	AddGOComponent(dead_sprite);
	//AddGOComponent(movable);
	turn_timer = new CS230::Timer(0.0);
	AddGOComponent(turn_timer);
}

void Trap::Update( [[maybe_unused]] double dt) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((turn_ended == false) && (is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {

		if (current_turn == 0) {
			current_turn = max_turn_count;
			is_alive = true;
		}
		else {
			--current_turn;
			is_alive = false;
		}

		//SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
		is_outdated = false;
		Engine::GetLogger().LogDebug("Enemy is updated");
		turn_timer->Set(turn_time);
	}
	if ((turn_ended == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (turn_timer->Remaining() == 0.0) {
			is_outdated = true;
			turn_ended = true;
		}
	}
	
}
void Trap::Draw(Math::TransformationMatrix camera_matrix) {
	if (is_alive == true) {
		alive_sprite->Draw(camera_matrix * GetMatrix());
	}
	else {
		dead_sprite->Draw(camera_matrix * GetMatrix());
	}
	//if (current_turn == 0) {
	//	movable->Draw(camera_matrix * GetMatrix());
	//}
}
bool Trap::CanCollideWith(GameObjectTypes other_object_type) {
	if ((Engine::GetGameStateManager().GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Enemy) && (other_object_type == GameObjectTypes::Player) &&(is_alive == true)) {
		return true;
	}
	return false;
}

void Trap::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(1);
		did_attack = true;
		player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
	}
}
