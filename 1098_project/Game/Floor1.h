/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/

#ifndef FLOOR1_H
#define FLOOR1_H
#pragma once
#include <vector>
#include "../Engine/GameState.h"
#include "../Engine/Camera.h"
#include "../Engine/Engine.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "FloorState.h"
#include "Floors.h"
#include "FloorStateManager.h"


class Floor1 : public FloorState {
public:
    Floor1(FloorStateManager& floorstatemanager);
    void Load() override;
    void Update(double) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Floor1";
    }

private:
    
    Map map;
    Player player;
    Enemy enemy;
    //CS230::Camera camera;
    Camera2D camera;
    FloorStateManager& floorstatemanager;
};

#endif // !MODE_H


