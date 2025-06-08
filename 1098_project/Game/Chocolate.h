#pragma once
#include "Item.h"

class Chocolate : public Item {
public:
	Chocolate(Math::ivec2 index);
	void ResolveCollision(GameObject* other_object) override;
};
