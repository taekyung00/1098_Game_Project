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
    int DrawPriority() const override { return 7; }
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    //void ResolveCollision(GameObject* other_object) override;
    virtual void ReachableIndexPush() = 0;
    virtual void ChangeMapDesign();

    virtual void Defeated() {};
    const bool GetIsOutdated() const { return is_outdated; }
    bool& SetIsOutdated() { return is_outdated; }
    const bool GetDidAttact() const { return did_attack; }
    //const bool GetMapChanged() const { return map_changed; }
    //bool& SetMapChanged() { return map_changed; }
    bool& SetDidAttact() { return did_attack; }

    const bool GetTurnEnded() const { return turn_ended; }
    bool& SetTurnEnded() { return turn_ended; }
protected:
    std::vector<Math::ivec2> reachable_indices;
    bool is_outdated = true;
    bool turn_ended = false;
    bool did_attack = false;
    //bool map_changed = false;
    void ChangeIndex();
    virtual void attack();
};
