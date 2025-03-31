/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/
#include "../Engine/Engine.h"
#include "Mode1.h"
#include "States.h"

Mode1::Mode1() : map( {8,8}), player(map) , enemy(map,player){}

void Mode1::Load() {
    Engine::GetWindow().Clear(0x00000000);
    map.Load();
    player.Load();
    enemy.Load();    
}

void Mode1::Update([[maybe_unused]] double dt) {
    map.Update();
    player.Update();
    enemy.Update();

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }

    if (player.GetIndex() == map.GetExitIndex()) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
    }
}

void Mode1::Unload() {
    map.Unload();
    player.Unload();
    enemy.Unload();
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0xFFFFFF00);
    map.Draw();
    player.Draw();
    enemy.Draw();
}