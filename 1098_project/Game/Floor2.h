/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/

#ifndef MODE2_H
#define MODE2_H
#pragma once
#include <vector>
#include "../Engine/GameState.h"
#include "../Engine/Camera.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "FloorState.h"
#include "FloorStateManager.h"


class Floor2 : public FloorState {
public:
    Floor2(FloorStateManager& floorstatemanager);
    void Load() override;
    void Update(double) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Floor2";
    }

private:
    //CS230::Camera camera;
    Map map;
    Player player;
    Enemy enemy;
    Camera2D camera;
    FloorStateManager& floorstatemanager;
};
#endif // !MODE_H
