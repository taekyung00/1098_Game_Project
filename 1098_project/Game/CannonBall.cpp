#include "CannonBall.h"
#include "Player.h"

CannonBall::CannonBall(Math::ivec2 index) :
	Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/CannonBall.spt", this));
}
void CannonBall::Update([[maybe_unused]]double dt) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if (turnmanager->GetCurrentTurn() == Turns::Player) {
		Destroy();
	}
}
void CannonBall::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(4);
		did_attack = true;
		player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
		Destroy();
	}
}

