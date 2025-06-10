#include "Axe.h"

Axe::Axe(Math::ivec2 start_index, ItemKind item_kind, UseItem use_item, UseItemRank use_item_rank) :
	Item(start_index, item_kind, use_item, use_item_rank)
{
	AddGOComponent(new CS230::Sprite("Assets/Axe.spt", this));
}

void Axe::ResolveCollision(GameObject* other_object) {
	//TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	
	if (other_object->Type() == GameObjectTypes::Player) {
		item_manager->PushUseItem(this);
		SetIndex() = { -1,-1 };
		SetPosition(Math::vec2{ -50.0, 300.0 } + start_position);

	}
}

