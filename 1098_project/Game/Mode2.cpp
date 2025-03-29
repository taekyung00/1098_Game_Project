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
#include "Mode2.h"
#include "States.h"

Mode2::Mode2() : map({ 13,13 }), player(map) {}

void Mode2::Load() {

    map.Load();
    player.Load();
}

void Mode2::Update([[maybe_unused]] double dt) {
    map.Update();
    player.Update();

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }

    if (player.GetIndex() == map.GetExitIndex()) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
    }
}

void Mode2::Unload() {
    map.Unload();
    player.Unload();
}

void Mode2::Draw() {
    Engine::GetWindow().Clear(0xFFFFFF00);
    map.Draw();
    player.Draw();
}