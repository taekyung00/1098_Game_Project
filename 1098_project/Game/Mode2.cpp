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

Mode2::Mode2() : map({ 5,5 }), player(map) , enemy(map,player){
    camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
    camera.offset = { float(Engine::GetWindow().GetSize().x / 2) - 150.f,float(Engine::GetWindow().GetSize().y / 2) - 150.f };
    camera.rotation = 0.f;
    camera.zoom = 1.f;
}

void Mode2::Load() {

    map.Load();
    player.Load();
    enemy.Load();
}

void Mode2::Update([[maybe_unused]] double dt) {
    map.Update();
    player.Update(dt);
    camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
    if (player.GetTimeLimit() > 2) {
        camera.zoom = 1.f;
    }
    else if (player.GetTimeLimit() <= 2 && player.GetTimeLimit() > 1) {
        camera.zoom = 1.5f;
    }
    else {
        camera.zoom = 2.f;
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }

    if (player.GetIndex() == map.GetExitIndex()) {
        /*Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));*/
        Engine::GetGameStateManager().ClearNextGameState();
    }
}

void Mode2::Unload() {
    map.Unload();
    player.Unload();
    enemy.Unload();
}

void Mode2::Draw() {
    BeginMode2D(camera);
    Engine::GetWindow().Clear(0xFFFFFF00);
    map.Draw();
    player.Draw();
    enemy.Draw();
    EndMode2D();
}