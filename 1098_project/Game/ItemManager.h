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
	void ClearItem();
private:
	std::vector<Item*> items;
	//void StoreItem();
};
