#include "Item.h"

Item::Item(Math::ivec2 start_index, ItemKind item_kind, UseItem use_item, UseItemRank use_item_rank, int life) :
	item_kind(item_kind),
	use_item(use_item),
	use_item_rank(use_item_rank),
	life(life),
	GameObject(start_index, 0.0, scale_const) {}

bool Item::CanCollideWith(GameObjectTypes other_object_type) {
	if (Engine::GetGameStateManager().GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Player && other_object_type == GameObjectTypes::Player) {
		return true;
	}
	return false;
}