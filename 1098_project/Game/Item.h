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
	Axe,
	Boots
};
enum class UseItemRank {
	Common,
	Rare,
	Unique,
	Legendary,
	None
};

class Item : public CS230::GameObject {
public:
	Item(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Drop, UseItem use_item = UseItem::None, UseItemRank use_item_rank = UseItemRank::None, int life = 1);
	GameObjectTypes Type() override { return GameObjectTypes::Item; }
	std::string TypeName() override { return "Item"; }
	int DrawPriority() const override { return 15; }
	bool CanCollideWith(GameObjectTypes other_object_type) override;
	//bool GetIt() { return get_it; };
	const int GetLife() const { return life; }
	int& SetLife()  { return life; }

	const int GetCost() const { return cost; }
	int& SetCost() { return cost; }

	const UseItemRank GetUseItemRank() const{ return use_item_rank; }
protected:
	ItemKind item_kind;
	UseItem use_item;
	UseItemRank use_item_rank;
	int life;
	int cost;
	bool is_get;
};
