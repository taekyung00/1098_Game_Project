#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Audio.h"

#include "Map.h"
#include "Player.h"

class Tutorial : public CS230::GameState {
public:
	Tutorial();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    std::string GetName() override {
        return "InGame";
    }
    static constexpr int MaxTurn = 100;
private:
    Map* map_ptr;
    Player* player_ptr;
    inline static Audio* current_audio_ptr;
    inline static Audio* tutorial_audio_ptr;
};