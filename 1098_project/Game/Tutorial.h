#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Audio.h"

#include "Map.h"
#include "Player.h"
#include "UI.h"

class Tutorial : public CS230::GameState {
public:
	Tutorial();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    std::string GetName() override {
        return "Tutorial";
    }
    static constexpr int MaxTurn = 100;
private:
    Map* map_ptr;
    Player* player_ptr;
    inline static Audio* current_audio_ptr;
    inline static Audio* tutorial_audio_ptr;

    CS230::Texture* turncount_texture;
    //CS230::Texture* turn_texture;
    CS230::Texture* push_button_texture;

    void update_turncount_text();
    void update_turn_text();
};