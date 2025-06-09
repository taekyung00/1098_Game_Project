#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Vec2.h"
#include "../Engine/Matrix.h"
#include "Tile.h"
#include "TurnManager.h"
#include "Turns.h"

enum class ItemKind {
	Drop,
	Use
};
enum class UseItem {
	None,
	Shield,
	Spear,
	Axe
};
enum class UseItemRank {
	None,
	Common,
	Rare,
	Unique
};

class Item : public CS230::GameObject {
public:
	Item(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Drop, UseItem use_item = UseItem::None, UseItemRank use_item_rank = UseItemRank::None);
	GameObjectTypes Type() override { return GameObjectTypes::Item; }
	std::string TypeName() override { return "Item"; }
	
	bool CanCollideWith(GameObjectTypes other_object_type) override;
	bool GetIt() { return get_it; };
protected:
	ItemKind item_kind;
	UseItem use_item;
	UseItemRank use_item_rank;
	bool get_it = false;
	virtual void Use() {};
};
