#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Vec2.h"
#include "Tile.h"
#include "TurnManager.h"
#include "Turns.h"

class Item : public CS230::GameObject {
public:
	Item(Math::ivec2 start_index);
	GameObjectTypes Type() override { return GameObjectTypes::Item; }
	std::string TypeName() override { return "Item"; }
	bool CanCollideWith(GameObjectTypes other_object_type) override;
};
