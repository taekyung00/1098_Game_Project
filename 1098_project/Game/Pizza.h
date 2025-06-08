#pragma once
#include "Item.h"
#include "InGame.h"

class Pizza : public Item
{
public:
	Pizza(Math::ivec2 index);
	void ResolveCollision(GameObject* other_object) override;
};
