#include "Arrow.h"

Arrow::Arrow(Math::ivec2 index) :
	 Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/Arrow.spt", this));
}

void Arrow::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(3);
		did_attack = true;
	}
}
