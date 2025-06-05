#pragma once
#include <vector>
#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"

#include "SpawnEnemy.h"
#include "Fonts.h"
#include "States.h"
#include "Map.h"
#include "Player.h"
#include "Door.h"
#include "Turns.h"
#include "TurnManager.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"

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
    static std::vector<Enemy*>& SetEnemies() { return Instance().enemies; }

    std::string GetName() override {
        return "InGame";
    }
    
private:
    const int max_turn = 10;

    Map* map_ptr;
    Player* player_ptr;
    std::vector<Enemy*> enemies;

    CS230::Texture* turncount_texture;
    CS230::Texture* turn_texture;
    
    
    void update_turncount_text();
    void update_turn_text();
};