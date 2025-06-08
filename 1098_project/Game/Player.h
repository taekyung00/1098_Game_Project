#pragma once

#include <vector>
#include "../Engine/GameObject.h"
#include "../Engine/Vec2.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"
#include "../Engine/Timer.h"

#include "States.h"
#include "GameObjectTypes.h"
#include "Tile.h"
#include "Map.h"
#include "TurnManager.h"
#include "Turns.h"
#include "SpawnEnemy.h"

class Player : public CS230::GameObject {
public:
	Player();
    void Update(double dt) override;
    GameObjectTypes Type() override { return GameObjectTypes::Player; }
    std::string TypeName() override { return "Player"; }

    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;
    
    
private:
    enum class Animations {
        Idle,
        Walking,
        Attacking
    };

    std::vector<Enemy*>& enemies ;
    TurnManager* turn_manager ;
    bool is_moving = true;
    bool did_nothing = false;
    Map* map;
    Audio* moving_sound_ptr;
    //CS230::Timer* after_move_timer;
    //static constexpr double after_move_time = 0.65;
    const Math::ivec2 start_index = { 2,0 };
    void move_left();
    void move_right();
    void move_top();
    void move_bottom();
    
};