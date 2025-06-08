#pragma once
#include <random>

#include "../Engine/Component.h"
#include "../Engine/Vec2.h"
#include "../Engine/GameObjectManager.h"



class ItemManager : public CS230::Component {
public:
	void DropItem(Math::ivec2 index);
	//void StoreItem();
};
