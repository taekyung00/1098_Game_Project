#include "Player.h"

#include "Enemy.h"
#include "InGame.h"

std::vector<Enemy*>* Player::enemies = nullptr;
Player::Player(Math::ivec2 start_index,TurnManager& turnmanager, Map& map) :
    turnmanager(turnmanager),
    map(map),
    moving_count(max_moving_count),
    is_moving(true),
    time_limit(start_time_limit),
    start_index(start_index),
    player_rect({ static_cast<float>(player_position.x),static_cast<float>(player_position.y),static_cast<float>(tile_size.x),static_cast<float>(tile_size.y) })
{
}

void Player::Load() {
    time_limit = start_time_limit;
    moving_count = max_moving_count;
    is_alive = true;
    did_attack = false;
    current_index = start_index;
    player_position = Math::vec2{ static_cast<double>(start_position.x), static_cast<double>(start_position.y) } + Math::vec2{ static_cast<double>(current_index.y * tile_size.y), static_cast<double>(current_index.x * tile_size.x) };
    player_rect = { static_cast<float>(player_position.x),static_cast<float>(player_position.y),static_cast<float>(tile_size.x),static_cast<float>(tile_size.y) };
}

void Player::Update(double dt/*,  Enemy& enemy*/) {
    did_attack = false;

    if (is_alive == false) {
        Engine::GetGameStateManager().ReloadState();
    }

    if (is_moving == true) {
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
            if (map.GetTileDesign()[current_index.x][current_index.y].isLeftEdge != true) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                for (Enemy* enemy : *(enemies)) {
                    if (current_index == enemy->GetNearIndex().at("right")) {
                        enemy->SetIsAlive() = false;
                        if (did_attack == false) {
                            did_attack = true;
                        }
                    }
                }
                if (did_attack == false) {
                    current_index.y--;
                }
            }
            moving_count--;
            time_limit = max_time_limit;
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy; 
            turnmanager.CountReset();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
            if (map.GetTileDesign()[current_index.x][current_index.y].isRightEdge != true) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                for (Enemy* enemy : *(enemies)) {
                    if (current_index == enemy->GetNearIndex().at("left")) {
                        enemy->SetIsAlive() = false;
                        if (did_attack == false) {
                            did_attack = true;
                        }
                    }
                }
                if (did_attack == false) {
                    current_index.y++;
                }
            }
            moving_count--;
            time_limit = max_time_limit;
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy;
            turnmanager.CountReset();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
            if (map.GetTileDesign()[current_index.x][current_index.y].isTopEdge != true) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                for (Enemy* enemy : *(enemies)) {
                    if (current_index == enemy->GetNearIndex().at("bottom")) {
                        enemy->SetIsAlive() = false;
                        if (did_attack == false) {
                            did_attack = true;
                        }
                    }
                }
                if (did_attack == false) {
                    current_index.x--;
                }
            }
            moving_count--;
            time_limit = max_time_limit;
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy;
            turnmanager.CountReset();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
            if (map.GetTileDesign()[current_index.x][current_index.y].isBotttomEdge != true) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                for (Enemy* enemy : *(enemies)) {
                    if (current_index == enemy->GetNearIndex().at("top")) {
                        enemy->SetIsAlive() = false;
                        if (did_attack == false) {
                            did_attack = true;
                        }
                    }
                }
                if (did_attack == false) {
                    current_index.x++;
                }
            }
            moving_count--;
            time_limit = max_time_limit;
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy;
            turnmanager.CountReset();
        }
    }
    //Engine::GetLogger().LogDebug(std::to_string(current_index.x)+", "+std::to_string(current_index.y));

    if (moving_count == 0) {
        is_moving = false;
        Engine::GetGameStateManager().ReloadState();
    }

    time_limit -= dt;
    // Engine::GetLogger().LogDebug("Time Limit :"+std::to_string(time_limit));

    if (time_limit <= 0.0) {
        Engine::GetGameStateManager().ReloadState();
    }
    player_position = Math::vec2{ static_cast<double>(start_position.x), static_cast<double>(start_position.y) } + Math::vec2{ static_cast<double>(current_index.y * tile_size.y), static_cast<double>(current_index.x * tile_size.x) };
    player_rect = { static_cast<float>(player_position.x),static_cast<float>(player_position.y),static_cast<float>(tile_size.x),static_cast<float>(tile_size.y) };

    if (CheckCollisionRecs(player_rect, map.GetDownStairsRect())) {
        //std::exit(EXIT_FAILURE);
        Engine::GetLogger().LogDebug("exit!");
    }
}

void Player::Draw() {
    DrawRectangle(static_cast<int>(player_position.x), static_cast<int>(player_position.y), tile_size.x, tile_size.y, BLUE);
    //temporary text background
    DrawRectangle(
        static_cast<int>(player_position.x + 10),
        static_cast<int>(player_position.y - 20),
        20,
        20,
        { 255,255,255,128 }
    );

    DrawText(
        TextFormat("%d", moving_count),
        static_cast<int>(player_position.x + 10),
        static_cast<int>(player_position.y - 20),
        20,
        RED);

    //temporary text background
    DrawRectangle(
        static_cast<int>(player_position.x - 40),
        static_cast<int>(player_position.y + 40),
        100,
        15,
        { 255,255,255,128 }
    );
    if (turnmanager.GetCurrentTurn() == TurnManager::Turns::player) {
        DrawText(
            TextFormat("PLAYER TURN"),
            static_cast<int>(player_position.x - 40),
            static_cast<int>(player_position.y + 40),
            15,
            RED);
    }
    else if(turnmanager.GetCurrentTurn() == TurnManager::Turns::enemy){
        DrawText(
            TextFormat("ENEMY TURN"),
            static_cast<int>(player_position.x - 40),
            static_cast<int>(player_position.y + 40),
            15,
            RED);
    }
    else if (turnmanager.GetCurrentTurn() == TurnManager::Turns::traps) {
        DrawText(
            TextFormat("TRAPS TURN"),
            static_cast<int>(player_position.x - 40),
            static_cast<int>(player_position.y + 40),
            15,
            RED);
    }

    //temporary text background
    /*DrawRectangle(
        player_position.x,
        player_position.y,
        20,
        20,
        { 255,255,255,128 }
    );*/
    if (time_limit <= start_time_limit && time_limit > start_time_limit - 1) {
        DrawText(
            TextFormat("5"),
            static_cast<int>(player_position.x),
            static_cast<int>(player_position.y),
            20,
            RED);
    } else if (time_limit <= start_time_limit - 1 && time_limit > start_time_limit - 2) {
        DrawText(
            TextFormat("4"),
            static_cast<int>(player_position.x),
            static_cast<int>(player_position.y),
            20,
            RED);
    } else if (time_limit <= start_time_limit - 2 && time_limit > start_time_limit - 3) {
        DrawText(
            TextFormat("3"),
            static_cast<int>(player_position.x),
            static_cast<int>(player_position.y),
            20,
            RED);
    } else if (time_limit <= start_time_limit - 3 && time_limit > start_time_limit - 4) {
        DrawText(
            TextFormat("2"),
            static_cast<int>(player_position.x),
            static_cast<int>(player_position.y),
            20,
            RED);
    } else {
        DrawText(
            TextFormat("1"),
            static_cast<int>(player_position.x),
            static_cast<int>(player_position.y),
            20,
            RED);
    }
}

void Player::Unload() {
    moving_count = max_moving_count;
    is_moving = true;
}

void Player::SetEnemiesReference(std::vector<Enemy*>& e)
{
    Player::enemies = &e;
}
