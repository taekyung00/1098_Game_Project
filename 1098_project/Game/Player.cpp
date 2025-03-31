#include "Player.h"

Player::Player(Map& map) : map(map) , moving_count(10), is_moving(true){}

void Player::Load() {
	if (map.GetIndex().x % 2 == 0) {
		index_start.x = map.GetIndex().x / 2 ;
	}
	else {
		index_start.x = map.GetIndex().y / 2 + 1;
	}

	if (map.GetIndex().y % 2 == 0) {
		index_start.y = map.GetIndex().y / 2 ;
	}
	else {
		index_start.y = map.GetIndex().y / 2 + 1;
	}
	index = index_start;
}

void Player::Update() {
	if (is_moving == true) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
			if (map.GetGrid()[index.x - 1][index.y] != Tile::wall) {
				index.x--;
				moving_count--;
			}
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
			if (map.GetGrid()[index.x + 1][index.y] != Tile::wall) {
				index.x++;
				moving_count--;
			}
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
			if (map.GetGrid()[index.x][index.y - 1] != Tile::wall) {
				index.y--;
				moving_count--;
			}
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
			if (map.GetGrid()[index.x][index.y + 1] != Tile::wall) {
				index.y++;
				moving_count--;
			}
		}
	}

	if (moving_count == 0) {
		is_moving = false;
	}
	
}

void Player::Draw() {
	Math::ivec2 center = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
	int radius = map.GetTileSize().y / 2;

	DrawCircle(
		center.x,
		center.y,
		radius, 
		YELLOW);

	DrawText(
		TextFormat("%d", moving_count),
		center.x-radius + 10,
		center.y-radius-20,
		20,
		RED);
}

void Player::Unload()
{
	moving_count = 10;
	is_moving = true;
}

