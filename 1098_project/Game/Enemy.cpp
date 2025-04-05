#include "Enemy.h"

Enemy::Enemy(TurnManager& turnmanager, Map& map, Player& player) :
	turnmanager(turnmanager),
	map(map), 
	player(player),
	is_attacking(false),
	attcak_count(1.0){
	
}

void Enemy::Load(){
	
	Math::ivec2 index_temp = { 0,0 };

	std::srand(std::time(nullptr));
	//take many times!!
	while (1) {
		index_temp = { rand() % map.GetCurrentIndex().x + 1 ,rand() % map.GetCurrentIndex().y + 1 };

		if ( 
			( ( (player.GetCurrentIndex().x - index_temp.x) >= 2) || ( (index_temp.x - player.GetCurrentIndex().x) >= 2) ) &&
			( ( (player.GetCurrentIndex().y - index_temp.y) >= 2) || ( (index_temp.y - player.GetCurrentIndex().y) >= 2) ) &&
			( ( (map.GetExitIndex().x       - index_temp.x) >= 2) || ( (index_temp.x - map.GetExitIndex().x      ) >= 2) ) &&
			( ( (map.GetExitIndex().y       - index_temp.y) >= 2) || ( (index_temp.y - map.GetExitIndex().y      ) >= 2) )
			) {

			
			index_start = index_temp;
			break;
			
			
		}
	}
	index = index_start;

	position = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
}

void Enemy::Update(double dt,bool& isEnemyTurn, bool& isPlayerTurn){

	attcak_count -= dt;
	if (attcak_count <= 0.0) {
		is_attacking = !is_attacking;
		attcak_count = 1.0;
	}

	if (is_attacking) {
		//left
		Math::ivec2 left_position = {
		map.GetStartPosition().x + (index.x-1) * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
		attackarms.push_back({ Vector2{ float(left_position.x),float(left_position.y) }, 15 });

		//right
		Math::ivec2 right_position = {
		map.GetStartPosition().x + (index.x + 1) * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
		attackarms.push_back({ Vector2{ float(right_position.x),float(right_position.y) }, 15 });

		//top
		Math::ivec2 top_position = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + (index.y-1) * map.GetTileSize().y + map.GetTileSize().y / 2 };
		attackarms.push_back({ Vector2{ float(top_position.x),float(top_position.y) }, 15 });

		//bottom
		Math::ivec2 bottom_position = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + (index.y + 1) * map.GetTileSize().y + map.GetTileSize().y / 2 };
		attackarms.push_back({ Vector2{ float(bottom_position.x),float(bottom_position.y) }, 15 });
	}
	else {
		attackarms.clear();
	}

}

void Enemy::Draw(){
	
	int radius = map.GetTileSize().y / 2;

	DrawCircle(
		position.x,
		position.y,
		radius,
		RED);
	if (attackarms.size() > 0) {
		for (int i = 0; i < attackarms.size(); ++i) {
			DrawCircle(
				attackarms[i].center.x,
				attackarms[i].center.y,
				attackarms[i].radius,
				RED);
		}
	}
}

void Enemy::Unload(){
	attackarms.clear();
}
