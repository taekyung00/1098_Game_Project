#pragma once
#include "Item.h"
#include "Tile.h"
#include "ItemManager.h"

class Spear : public Item {
public:
	Spear(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Spear, UseItemRank use_item_rank = UseItemRank::Common);
	void ResolveCollision(GameObject* other_object) override;
};