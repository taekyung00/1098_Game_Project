#include "Enemy.h"
#include "InGame.h"

bool isNear(const Math::ivec2& enemy_pos, const Math::ivec2& player_pos) {
	int deltaX = abs(enemy_pos.x - player_pos.x);
	int deltaY = abs(enemy_pos.y - player_pos.y);

	// if X and Y are under 1 tile, then return true
	return (deltaX <= 1 && deltaY <= 1) && (deltaX !=0 || deltaY != 0 );
}

Enemy::Enemy(TurnManager& turnmanager, Map& map, Player& player) :
	turnmanager(turnmanager),
	map(map),
	player(player),
	is_attacking(false),
	is_alive(true),
	attcak_count(1.0) {

}

void Enemy::Load() {
	is_alive = true;
	index = { 7, 5 };

	position = {
		map.GetStartPosition().x + index.x * tile_size.x + tile_size.x / 2,
		map.GetStartPosition().y + index.y * tile_size.y + tile_size.y / 2 };
}

void Enemy::Attack() {
	if (is_alive == false) {
		Unload();
		return;
	}
	attackarms.clear();
	if (is_attacking) {
		//left
		Math::ivec2 left_position = {
		map.GetStartPosition().x + (index.x - 1) * tile_size.x + tile_size.x / 2,
		map.GetStartPosition().y + index.y * tile_size.y + tile_size.y / 2 };
		attackarms.push_back({ Vector2{ float(left_position.x),float(left_position.y) }, 15 });

		//right
		Math::ivec2 right_position = {
		map.GetStartPosition().x + (index.x + 1) * tile_size.x + tile_size.x / 2,
		map.GetStartPosition().y + index.y * tile_size.y + tile_size.y / 2 };
		attackarms.push_back({ Vector2{ float(right_position.x),float(right_position.y) }, 15 });

		//top
		Math::ivec2 top_position = {
		map.GetStartPosition().x + index.x * tile_size.x + tile_size.x / 2,
		map.GetStartPosition().y + (index.y - 1) * tile_size.y + tile_size.y / 2 };
		attackarms.push_back({ Vector2{ float(top_position.x),float(top_position.y) }, 15 });

		//bottom
		Math::ivec2 bottom_position = {
		map.GetStartPosition().x + index.x * tile_size.x + tile_size.x / 2,
		map.GetStartPosition().y + (index.y + 1) * tile_size.y + tile_size.y / 2 };
		attackarms.push_back({ Vector2{ float(bottom_position.x),float(bottom_position.y) }, 15 });
	}

	if (attackarms.size() > 0) {
		Vector2 temp_player_position = { player.GetPosition().x,player.GetPosition().y };
		for (int i = 0; i < attackarms.size(); i++) {
			if (CheckCollisionCircles(temp_player_position, player.GetRadius(), attackarms[i].center, attackarms[i].radius)) {
				//player.GetMovingCount()--;
				player.SetIsAttacked() = true;
				is_attacking = !is_attacking;
				Engine::GetLogger().LogDebug("Enemy attack");
				attackarms.clear();
				break;
			}
		}
	}

}

void Enemy::Update(double dt, bool& isEnemyTurn, bool& isPlayerTurn) {
	if (is_alive == false) {
		turnmanager.EnemyToPlayer();
		Unload();
		return;
	}
    Math::ivec2 playerIndex = player.GetCurrentIndex();
    
    attcak_count -= dt;
    if (attcak_count <= 0.0) {
		if (is_attacking == true) {
			is_attacking = false;
		}
		else {
			is_attacking = true;
		}
        attcak_count = 1.0;
    }
	
    if (isNear(index, playerIndex)) {
		Attack();
        turnmanager.EnemyToPlayer();
        return;
    }


    
    int deltaX = playerIndex.x - index.x;
    int deltaY = playerIndex.y - index.y;
    Math::ivec2 candidate = index;
    
    if (abs(deltaX) >= abs(deltaY) && deltaX != 0) {
        candidate.x += (deltaX > 0) ? 1 : -1;
    }
    else if (deltaY != 0) {
        candidate.y += (deltaY > 0) ? 1 : -1;
    }
    
    if (map.isAble(candidate))
        index = candidate;
    
    position = {
        map.GetStartPosition().x + index.x * tile_size.x + tile_size.x / 2,
        map.GetStartPosition().y + index.y * tile_size.y + tile_size.y / 2
    };
    
    //turnmanager.EnemyToPlayer();
}

void Enemy::Draw() {

	int radius = tile_size.y / 2;

	DrawCircle(
		position.x,
		position.y,
		radius,
		{ 100, 255, 100, 180 });
	if (attackarms.size() > 0) {
		for (int i = 0; i < attackarms.size(); ++i) {
			DrawCircle(
				attackarms[i].center.x,
				attackarms[i].center.y,
				attackarms[i].radius,
				{ 100, 255, 100, 180 });
		}
	}
}

void Enemy::Unload() {
	attackarms.clear();
	position = { -100,-100 };
}
