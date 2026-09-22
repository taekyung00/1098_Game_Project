#pragma once
#include "Item.h"
#include "Tile.h"
#include "ItemManager.h"

class Spear : public Item {
public:
	Spear(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Spear, UseItemRank use_item_rank = UseItemRank::Common);
	GameObjectTypes Type() override { return GameObjectTypes::Spear; }
	std::string TypeName() override { return "Spear"; }
	void ResolveCollision(GameObject* other_object) override;
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
private:
	CS230::Texture* cost_texture;
	int temp_life;
};