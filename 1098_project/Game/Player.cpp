#include "Player.h"

#include "Enemy.h"
#include "InGame.h"

std::vector<Enemy*>* Player::enemies = nullptr;
Player::Player(TurnManager& turnmanager, Map& map) : turnmanager(turnmanager),
                                                     map(map),
                                                     moving_count(max_moving_count),
                                                     is_moving(true),
                                                     time_limit(start_time_limit) {
}

void Player::Load() {
    time_limit = start_time_limit;
    is_attacked = false;
    moving_count = max_moving_count;
    current_index = {3, 3};
    player_position = Math::vec2{ static_cast<double>(start_position.x), static_cast<double>(start_position.y) } + Math::vec2{ static_cast<double>(current_index.y * tile_size.y), static_cast<double>(current_index.x * tile_size.x) };
    player_rect = { static_cast<float>(player_position.x),static_cast<float>(player_position.y),static_cast<float>(tile_size.x),static_cast<float>(tile_size.y) };
}

void Player::Update(double dt/*,  Enemy& enemy*/) {
    if (is_alive == false) {
        Engine::GetGameStateManager().ReloadState();
    }
    if (is_moving == true) {
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
            if (
                map.GetTileDesign()[current_index.x][current_index.y].isLeftEdge != true
                ) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                /*for (Enemy* enemy : *(enemies)) {
                    for(enemy)
                }*/
                current_index.y--;
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            } else {
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            }
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy; 
            turnmanager.CountReset();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
            if (
                map.GetTileDesign()[current_index.x][current_index.y].isRightEdge != true
                ) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                current_index.y++;
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            } else {
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            }
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy;
            turnmanager.CountReset();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
            if (
                map.GetTileDesign()[current_index.x][current_index.y].isTopEdge != true
                ) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                current_index.x--;
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            } else {
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            }
            turnmanager.SetCurrentTurn() = TurnManager::Turns::enemy;
            turnmanager.CountReset();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
            if (
                map.GetTileDesign()[current_index.x][current_index.y].isBotttomEdge != true
                ) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                current_index.x++;
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            } else {
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            }
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
        player_position.x  + 10,
        player_position.y  - 20,
        20,
        20,
        { 255,255,255,128 }
    );

    DrawText(
        TextFormat("%d", moving_count),
        player_position.x  + 10,
        player_position.y  - 20,
        20,
        RED);

    //temporary text background
    DrawRectangle(
        player_position.x - 40,
        player_position.y + 40,
        100,
        15,
        { 255,255,255,128 }
    );
    if (turnmanager.GetCurrentTurn() == TurnManager::Turns::player) {
        DrawText(
            TextFormat("PLAYER TURN"),
            player_position.x-40,
            player_position.y + 40,
            15,
            RED);
    }
    else if(turnmanager.GetCurrentTurn() == TurnManager::Turns::enemy){
        DrawText(
            TextFormat("ENEMY TURN"),
            player_position.x-40,
            player_position.y + 40,
            15,
            RED);
    }
    else if (turnmanager.GetCurrentTurn() == TurnManager::Turns::traps) {
        DrawText(
            TextFormat("TRAPS TURN"),
            player_position.x - 40,
            player_position.y + 40,
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
            player_position.x,
            player_position.y,
            20,
            RED);
    } else if (time_limit <= start_time_limit - 1 && time_limit > start_time_limit - 2) {
        DrawText(
            TextFormat("4"),
            player_position.x,
            player_position.y,
            20,
            RED);
    } else if (time_limit <= start_time_limit - 2 && time_limit > start_time_limit - 3) {
        DrawText(
            TextFormat("3"),
            player_position.x,
            player_position.y,
            20,
            RED);
    } else if (time_limit <= start_time_limit - 3 && time_limit > start_time_limit - 4) {
        DrawText(
            TextFormat("2"),
            player_position.x,
            player_position.y,
            20,
            RED);
    } else {
        DrawText(
            TextFormat("1"),
            player_position.x,
            player_position.y,
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
