#ifndef INGAME_H
#define INGAME_H
#pragma once

#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Camera.h"
#include "../Engine/GameState.h"


#include "Player.h"
#include "Enemy.h"

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

    Math::ivec2 floor1_index = { 8,8 };
    Math::ivec2 floor2_index = { 5,5 };
    Math::ivec2 current_map_index ;
    Map map;
    Player player;
    Enemy enemy;
    Camera2D camera;

    bool isPlayerTurn = true;
    bool isEnemyTurn = false;
};
#endif // !MODE_H


