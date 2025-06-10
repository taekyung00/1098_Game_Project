#pragma once
#include <random>
#include <vector>

#include "../Engine/Component.h"
#include "../Engine/Vec2.h"
#include "../Engine/GameObjectManager.h"
#include "Item.h"



class ItemManager : public CS230::Component {
public:
	void DropItem(Math::ivec2 index);
	void StoreItem(Math::ivec2 index);
	void ClearDropItem();
	void EraseDropItem(Item* item);
	void EraseUseItem(Item* item);
	void PushUseItem(Item* item);

	const std::vector<Item*>& GetUseItems() const { return use_items; }
	std::vector<Item*>& SetUseItems() { return use_items; }

private:
	std::vector<Item*> drop_items;
	std::vector<Item*> use_items;
	//void StoreItem();
};
