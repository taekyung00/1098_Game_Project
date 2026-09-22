#pragma once
#include "Item.h"
#include "Tile.h"
#include "ItemManager.h"

class Shield : public Item {
public:
	Shield(Math::ivec2 start_index, ItemKind item_kind = ItemKind::Use, UseItem use_item = UseItem::Shield, UseItemRank use_item_rank = UseItemRank::Common);
	GameObjectTypes Type() override { return GameObjectTypes::Shield; }
	std::string TypeName() override { return "Shield"; }
	void ResolveCollision(GameObject* other_object) override;
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
private:
	CS230::Texture* cost_texture;
	int temp_life;
};
