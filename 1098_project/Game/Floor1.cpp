/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 12, 2025
*/

#include "Floor1.h"
#include "States.h"

Floor1::Floor1(FloorStateManager& floorstatemanager) : map({ 8,8 }), player(map,floorstatemanager), enemy(map, player), floorstatemanager(floorstatemanager) {
    
    camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
    camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
    
    camera.rotation = 0.f;
    camera.zoom = 1.f;
}

void Floor1::Load() {
    
    map.Load();
    player.Load();
    enemy.Load();   
    camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
}

void Floor1::Update([[maybe_unused]] double dt) {
    map.Update();
    
    enemy.Update(dt);
    player.Update(dt,enemy);
    if (player.GetTimeLimit() > 2) {
        camera.zoom = 1.f;
    }
    else if (player.GetTimeLimit() <= 2 && player.GetTimeLimit() > 1) {
        camera.zoom = 1.5f;
    }
    else {
        camera.zoom = 2.f;
    }
    camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        floorstatemanager.ReloadFloor();
    }

    if (player.GetIndex() == map.GetExitIndex()) {
        floorstatemanager.SetNextFloor(static_cast<int>(Floors::floor2));
    }
}

void Floor1::Unload() {
    map.Unload();
    player.Unload();
    enemy.Unload();
}

void Floor1::Draw() {
    BeginMode2D(camera);
    Engine::GetWindow().Clear(0xFFFFFF00);

    map.Draw();
    player.Draw();
    enemy.Draw();
    EndMode2D();
}