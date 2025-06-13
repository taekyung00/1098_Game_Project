#pragma once
#include "Item.h"
#include "Tile.h"
#include "ItemManager.h"

class Axe : public Item {
public:
	Axe(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Axe, UseItemRank use_item_rank = UseItemRank::Common);
	GameObjectTypes Type() override { return GameObjectTypes::Axe; }
	std::string TypeName() override { return "Axe"; }
	void ResolveCollision(GameObject* other_object) override;
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
private:
	CS230::Texture* cost_texture;
};
