/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/

#ifndef MODE1_H
#define MODE1_H
#pragma once
#include <vector>
#include "../Engine/GameState.h"
#include "../Engine/Camera.h"
#include "../Game/Map.h"
#include "../Game/Player.h"


class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update(double) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode1";
    }

private:
    //CS230::Camera camera;
    Map map;
    Player player;

};
#endif // !MODE_H


