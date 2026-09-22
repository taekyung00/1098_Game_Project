#include "Chocolate.h"

Chocolate::Chocolate(Math::ivec2 index) : 
	Item(index)
{
	AddGOComponent(new CS230::Sprite("Assets/Chocolate.spt", this));
}

void Chocolate::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	if (other_object->Type() == GameObjectTypes::Player) {
		turn_manager->Add(3);
		item_manager->EraseDropItem(this);
	}
}