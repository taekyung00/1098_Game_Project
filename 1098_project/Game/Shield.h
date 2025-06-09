#pragma once
#include "Item.h"
#include "Tile.h"

class Shield : public Item {
public:
	Shield(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Shield, UseItemRank use_item_rank = UseItemRank::Common);
	void ResolveCollision(GameObject* other_object) override;
};
