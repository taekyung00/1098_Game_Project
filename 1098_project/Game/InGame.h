#pragma once
#include <vector>
#include <raylib.h>

#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"


#include "Fonts.h"
#include "States.h"
#include "Map.h"

#include "Door.h"
#include "Turns.h"
#include "TurnManager.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "EnemyManager.h"

class Player;
class InGame : public CS230::GameState {
public:
    static InGame& Instance() {
        static InGame instance;
        return instance; //why we have to keep track of "instance" ???
    }
    InGame();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    static void ChangeAudio();
    std::string GetName() override {
        return "InGame";
    }
    static constexpr int MaxTurn = 100;
    
private:
    Map* map_ptr;
    Player* player_ptr;

    CS230::Texture* turncount_texture;
    CS230::Texture* turn_texture;
    CS230::Texture* push_button_texture;

    inline static Audio* current_audio_ptr;
    inline static Audio* stage1_audio_ptr;
    inline static Audio* stage2_audio_ptr;
    inline static Audio* stage3_audio_ptr;
    
    
    void update_turncount_text();
    void update_turn_text();
    
};