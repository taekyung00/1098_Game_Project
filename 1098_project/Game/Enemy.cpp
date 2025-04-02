#include "Enemy.h"

Enemy::Enemy(Map& map, Player& player) : map(map), player(player), is_attacking(false),attcak_count(1.0){
	
}

void Enemy::Load(){
	
	Math::ivec2 index_temp = { 0,0 };

	std::srand(std::time(nullptr));
	//take many times!!
	while (1) {
		index_temp = { rand() % map.GetIndex().x + 1 ,rand() % map.GetIndex().y + 1 };

		if ( 
			( ( (player.GetIndex().x - index_temp.x) >= 2) || ( (index_temp.x - player.GetIndex().x) >= 2) ) &&
			( ( (player.GetIndex().y - index_temp.y) >= 2) || ( (index_temp.y - player.GetIndex().y) >= 2) )
			) {

			if (index_temp != map.GetExitIndex()) {
				index_start = index_temp;
				break;
			}
			
		}
	}
	index = index_start;

	position = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
}

void Enemy::Update(double dt){
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
