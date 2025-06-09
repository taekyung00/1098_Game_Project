#include "Omurice.h"

Omurice::Omurice(Math::ivec2 index) : 
	Item(index)
{
	AddGOComponent(new CS230::Sprite("Assets/Omurice.spt", this));
}

void Omurice::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if (other_object->Type() == GameObjectTypes::Player) {
		turn_manager->Add(5);
		Destroy();
	}
}
