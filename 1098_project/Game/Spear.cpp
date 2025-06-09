#include "Spear.h"

Spear::Spear(Math::ivec2 start_index, ItemKind item_kind, UseItem use_item, UseItemRank use_item_rank) :
	Item(start_index, item_kind, use_item, use_item_rank)
{
	AddGOComponent(new CS230::Sprite("Assets/Spear.spt", this));
}

void Spear::ResolveCollision(GameObject* other_object) {
	//TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>(); 
		if (other_object->Type() == GameObjectTypes::Player) {
			get_it = true;
			SetIndex() = { -1,-1 };
			SetPosition(Math::vec2{ -50.0, 200.0 } + start_position);
		}
}
