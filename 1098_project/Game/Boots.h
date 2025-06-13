#pragma once
#include "Item.h"
#include "Tile.h"
#include "ItemManager.h"

class Boots : public Item {
public:
	Boots(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Boots, UseItemRank use_item_rank = UseItemRank::Common);
	GameObjectTypes Type() override { return GameObjectTypes::Boots; }
	std::string TypeName() override { return "Boots"; }
	void ResolveCollision(GameObject* other_object) override;
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
private:
	CS230::Texture* cost_texture;
};