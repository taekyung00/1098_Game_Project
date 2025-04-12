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
#include "../Engine/Audio.h"

Mode1::Mode1() : map({ 8,8 }), player(map), enemy(map, player), audio("Sounds/Drum,Metronom.wav") {
    
    camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
    camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
    
    camera.rotation = 0.f;
    camera.zoom = 1.f;
}

void Mode1::Load() {
    
    map.Load();
    player.Load();
    enemy.Load();   
    camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
    audio.SetLooping(true);
    audio.Play();
}

void Mode1::Update([[maybe_unused]] double dt) {
    map.Update();
    
    enemy.Update(dt);
    player.Update(dt,enemy);
    audio.Update();
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
    audio.Stop();
}

void Mode1::Draw() {
    BeginMode2D(camera);
    Engine::GetWindow().Clear(0xFFFFFF00);

    map.Draw();
    player.Draw();
    enemy.Draw();
    EndMode2D();
}