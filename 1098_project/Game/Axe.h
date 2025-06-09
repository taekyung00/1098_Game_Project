#pragma once
#include "Item.h"
#include "Tile.h"

class Axe : public Item {
public:
	Axe(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Axe, UseItemRank use_item_rank = UseItemRank::Common);
	void ResolveCollision(GameObject* other_object) override;
};
