#include "Item.h"

Item::Item(Math::ivec2 start_index) :
	GameObject(start_index, 0.0, scale_const){}

bool Item::CanCollideWith(GameObjectTypes other_object_type) {
	if (Engine::GetGameStateManager().GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Player && other_object_type == GameObjectTypes::Player) {
		return true;
	}
	return false;
}