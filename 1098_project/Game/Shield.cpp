#include "Shield.h"

Shield::Shield(Math::ivec2 start_index, ItemKind item_kind, UseItem use_item, UseItemRank use_item_rank) :
	Item(start_index,item_kind,use_item,use_item_rank)
{
	AddGOComponent(new CS230::Sprite("Assets/Shield.spt", this));
}

void Shield::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
		if (other_object->Type() == GameObjectTypes::Player) {
			get_it = true;
		}
}

void Shield::Draw(Math::TransformationMatrix camera_matrix) {

}