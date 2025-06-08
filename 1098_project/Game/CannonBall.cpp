#include "CannonBall.h"

CannonBall::CannonBall(Math::ivec2 index) :
	Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/CannonBall.spt", this));
}

void CannonBall::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(1);
		did_attack = true;
	}
}

