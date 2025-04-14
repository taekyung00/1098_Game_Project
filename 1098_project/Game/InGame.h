#ifndef INGAME_H
#define INGAME_H
#pragma once



#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Camera.h"
#include "../Engine/GameState.h"
#include "../Engine/Audio.h"


#include "Player.h"
#include "Enemy.h"
#include "TurnManager.h"


#include <vector>


class InGame : public CS230::GameState {
public:

    InGame();
    void Load() override;
    void Update(double) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "InGame";
    }


private:
    static constexpr double max_turn_count = 3.0;

    Math::ivec2 floor1_index = { 8,8 };
    Math::ivec2 floor2_index = { 5,5 };
    Math::ivec2 current_map_index;
    TurnManager turnmanager;
    Map map;
    Player player;
    Enemy enemy;
    Camera2D camera;
    Audio audio;
};

#endif // !MODE_H


