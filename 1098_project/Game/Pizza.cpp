
#include "Pizza.h"

Pizza::Pizza(Math::ivec2 index) : 
	Item(index)
{
	AddGOComponent(new CS230::Sprite("Assets/Pizza.spt", this));
}

void Pizza::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	if (other_object->Type() == GameObjectTypes::Player) {
		turn_manager->Add(InGame::MaxTurn);
		Destroy();
		item_manager->EraseDropItem(this);
	}
}
