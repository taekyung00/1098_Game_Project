#include "Player.h"

#include "Enemy.h"

Player::Player(TurnManager& turnmanager, Map& map) : turnmanager(turnmanager),
                                                     map(map),
                                                     moving_count(10),
                                                     is_moving(true),
                                                     time_limit(start_time_limit) {
    radius = map.GetTileSize().y / 2;
}

void Player::Load() {
    time_limit = start_time_limit;
    is_attacked = false;

    /*if (map.GetCurrentIndex().x % 2 == 0) {
            index_start.x = map.GetCurrentIndex().x / 2;
    }
    else {
            index_start.x = map.GetCurrentIndex().y / 2 + 1;
    }

    if (map.GetCurrentIndex().y % 2 == 0) {
            index_start.y = map.GetCurrentIndex().y / 2;
    }
    else {
            index_start.y = map.GetCurrentIndex().y / 2 + 1;
    }*/
    current_index = {3, 3};
    player_position = {
        map.GetStartPosition().x + current_index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
        map.GetStartPosition().y + current_index.y * map.GetTileSize().y + map.GetTileSize().y / 2};
}

void Player::Update(double dt, const Enemy& enemy, bool& isPlayerTurn, bool& isEnemyTurn) {
    if (is_moving == true) {
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
            // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.x][current_index.y]));
            if (/*map.GetGrid()[current_index.x - 1][current_index.y] != Tile::wall*/
                /*map.GetTileDesign()[current_index.y][current_index.x].tile_number != 1 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 4 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 9 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 12 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 17 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 20*/
                map.GetTileDesign()[current_index.y][current_index.x].isLeftEdge != true
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
            turnmanager.PlayerToEnemy();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
            if (/*map.GetTileDesign()[current_index.y][current_index.x].tile_number != 3 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 6 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 11 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 14 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 19 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 22*/
                map.GetTileDesign()[current_index.y][current_index.x].isRightEdge != true
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
            turnmanager.PlayerToEnemy();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
            if (/*map.GetTileDesign()[current_index.y][current_index.x].tile_number != 1 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 2 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 3 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 4 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 5 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 6*/
                map.GetTileDesign()[current_index.y][current_index.x].isTopEdge != true
                ) {
                // Engine::GetLogger().LogDebug(std::to_string(map.GetTileDesign()[current_index.y][current_index.x]));
                current_index.y--;
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            } else {
                moving_count--;
                time_limit = max_time_limit;
                is_attacked = false;
            }
            turnmanager.PlayerToEnemy();
        }
        if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
            if (/*map.GetTileDesign()[current_index.y][current_index.x].tile_number != 17 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 18 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 19 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 20 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 21 &&
                map.GetTileDesign()[current_index.y][current_index.x].tile_number != 22*/
                map.GetTileDesign()[current_index.y][current_index.x].isBotttomEdge != true
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
            turnmanager.PlayerToEnemy();
        }
    }

    if (moving_count == 0) {
        is_moving = false;
        Engine::GetGameStateManager().ReloadState();
    }

    time_limit -= dt;
    // Engine::GetLogger().LogDebug("Time Limit :"+std::to_string(time_limit));

    if (time_limit <= 0.0) {
        Engine::GetGameStateManager().ReloadState();
    }
    player_position = {
        map.GetStartPosition().x + current_index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
        map.GetStartPosition().y + current_index.y * map.GetTileSize().y + map.GetTileSize().y / 2};

    if (enemy.GetArms().size() > 0) {
        Vector2 temp_player_position = {player_position.x, player_position.y};
        for (int i = 0; i < enemy.GetArms().size(); i++) {
            if (CheckCollisionCircles(temp_player_position, radius, enemy.GetArms()[i].center, enemy.GetArms()[i].radius) &&
                (is_attacked == false)) {
                moving_count--;
                is_attacked = true;
                Engine::GetLogger().LogDebug("player attacked!");
                turnmanager.PlayerToEnemy();
                break;
            }
        }
    }
}

void Player::Draw() {
    DrawCircle(
        player_position.x,
        player_position.y,
        radius,
        YELLOW);

    DrawText(
        TextFormat("%d", moving_count),
        player_position.x - radius + 10,
        player_position.y - radius - 20,
        20,
        RED);
    if (turnmanager.isplayerturn) {
        DrawText(
            TextFormat("PLAYER TURN"),
            player_position.x-40,
            player_position.y + 40,
            15,
            RED);
    }
    else {
        DrawText(
            TextFormat("ENEMY TURN"),
            player_position.x-40,
            player_position.y + 40,
            15,
            RED);
    }

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
    moving_count = 10;
    is_moving = true;
}
