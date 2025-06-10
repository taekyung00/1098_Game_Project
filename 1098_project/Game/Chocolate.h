#pragma once
#include "Item.h"
#include "ItemManager.h"

class Chocolate : public Item {
public:
	Chocolate(Math::ivec2 index);
	void ResolveCollision(GameObject* other_object) override;

};
