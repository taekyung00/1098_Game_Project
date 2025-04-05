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
#include "Floor2.h"
#include "States.h"

Floor2::Floor2(FloorStateManager& floorstatemanager) : map({ 5,5 }), player(map,floorstatemanager) , enemy(map,player), floorstatemanager(floorstatemanager) {
    camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
    camera.offset = { float(Engine::GetWindow().GetSize().x / 2) - 150.f,float(Engine::GetWindow().GetSize().y / 2) - 150.f };
    camera.rotation = 0.f;
    camera.zoom = 1.f;
}

void Floor2::Load() {

    map.Load();
    player.Load();
    enemy.Load();
    camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
}

void Floor2::Update([[maybe_unused]] double dt) {
    map.Update();
    enemy.Update(dt);
    player.Update(dt,enemy);
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
        floorstatemanager.ReloadFloor();
    }

    if (player.GetIndex() == map.GetExitIndex()) {
        floorstatemanager.ClearNextFloor();
    }
}

void Floor2::Unload() {
    map.Unload();
    player.Unload();
    enemy.Unload();
}

void Floor2::Draw() {
    BeginMode2D(camera);
    Engine::GetWindow().Clear(0xFFFFFF00);
    map.Draw();
    player.Draw();
    enemy.Draw();
    EndMode2D();
}