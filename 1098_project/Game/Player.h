#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <fstream>

#include "../Engine/Camera.h"
#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"

#include "Map.h"
#include "TurnManager.h"
#include "Enemy.h"


class Enemy;
class Player {
public:
    Player(TurnManager& turnmanager, Map& map);
    void Load();
    void Update(double dt,  Enemy& enemy);
    void Draw();
    void Unload();
    const Math::ivec2& GetCurrentIndex() const { return current_index; }
    const Math::ivec2& GetPosition() const { return player_position; }
    const double& GetTimeLimit() const { return time_limit; }
    const bool& GetIsAttacked() const { return is_attacked; }
    bool& SetIsAttacked() { return is_attacked; }
    const int& GetRadius() const { return radius; }
    const int& GetMovingCount() const { return moving_count; }
    int& SetMovingCount() { return moving_count; }

private:
    TurnManager& turnmanager;
    Map& map;
    CS230::Sprite sprite;

    // CS230::Camera& camera;

    Math::ivec2 index_start;
    Math::ivec2 current_index;
    Math::ivec2 player_position;

    int radius;

    const int max_moving_count = 10;
    int moving_count;
    double start_time_limit = 5;
    double max_time_limit = 2;
    double time_limit;
    bool is_moving;
    bool is_attacked = false;
};
#endif  // !PLAYER_H