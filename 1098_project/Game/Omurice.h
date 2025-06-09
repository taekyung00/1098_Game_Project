#pragma once
#include "Item.h"
#include "ItemManager.h"

class Omurice : public Item {
public:
	Omurice(Math::ivec2 index);
	void ResolveCollision(GameObject* other_object) override;

};
