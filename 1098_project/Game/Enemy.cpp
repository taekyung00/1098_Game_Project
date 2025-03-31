#include "Enemy.h"

Enemy::Enemy(Map& map, Player& player) : map(map), player(player){}

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
}

void Enemy::Update()
{
}

void Enemy::Draw(){
	Math::ivec2 center = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
	int radius = map.GetTileSize().y / 2;

	DrawCircle(
		center.x,
		center.y,
		radius,
		RED);
}

void Enemy::Unload()
{
}
