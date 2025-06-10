#include "Spear.h"
#include "Player.h"

Spear::Spear(Math::ivec2 start_index, ItemKind item_kind, UseItem use_item, UseItemRank use_item_rank) :
	Item(start_index, item_kind, use_item, use_item_rank)
{
	AddGOComponent(new CS230::Sprite("Assets/Spear.spt", this));
	switch (use_item_rank)
	{
	case UseItemRank::Common:
		life = 1;
		cost = 3;
		break;
	case UseItemRank::Rare:
		life = 2;
		cost = 4;
		break;
	case UseItemRank::Unique:
		life = 3;
		cost = 5;
		break;
	case UseItemRank::Legendary:
		life = 5;
		cost = 6;
		break;
	}
}

void Spear::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
		if (other_object->Type() == GameObjectTypes::Player) {
			item_manager->PushUseItemToPlayer(this);
			turn_manager->Sub(cost);
			SetIndex() = { -10,-10 };
			SetPosition({ -100.0, -100.0 });
		}
}

void Spear::Update([[maybe_unused]] double dt) {
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if (life <= 0) {
		item_manager->EraseUseItem(this);
		player->EraseUseItem(this);
	}
}