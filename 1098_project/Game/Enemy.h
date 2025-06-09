#pragma once
#include <map>
#include <vector>
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Vec2.h"
#include "Tile.h"
#include "TurnManager.h"
#include "Map.h"


class Enemy : public CS230::GameObject {
public:
	Enemy(Math::ivec2 start_index);
    void Update(double dt) override;
    GameObjectTypes Type() override { return GameObjectTypes::Enemy; }
    std::string TypeName() override { return "Enemy"; }
    //int DrawPriority() const override { return 3; }
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    //void ResolveCollision(GameObject* other_object) override;
    virtual void ReachableIndexPush() = 0;
    //virtual void ChangeMapDesign();
    const bool GetIsOutdated() const { return is_outdated; }
    const bool GetDidAttact() const { return did_attack; }
    bool& SetDidAttact() { return did_attack; }
protected:
    std::vector<Math::ivec2> reachable_indices;
    bool is_outdated = true;
    bool did_attack = false;
    void ChangeIndex();
};
