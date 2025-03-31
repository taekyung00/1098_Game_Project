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
	player_position = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
	
}

void Player::Update(double dt) {
	if (is_moving == true) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
			if (map.GetGrid()[index.x - 1][index.y] != Tile::wall) {
				index.x--;
				moving_count--;
				time_limit = 3;
			}
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
			if (map.GetGrid()[index.x + 1][index.y] != Tile::wall) {
				index.x++;
				moving_count--;
				time_limit = 3;
			}
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
			if (map.GetGrid()[index.x][index.y - 1] != Tile::wall) {
				index.y--;
				moving_count--;
				time_limit = 3;
			}
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
			if (map.GetGrid()[index.x][index.y + 1] != Tile::wall) {
				index.y++;
				moving_count--;
				time_limit = 3;
			}
		}
	}

	if (moving_count == 0) {
		is_moving = false;
	}

	time_limit -= dt;
	Engine::GetLogger().LogDebug(std::to_string(time_limit));

	if (time_limit <= 0.0) {
		Engine::GetGameStateManager().ReloadState();
		time_limit = 3;
	}
	player_position = {
		map.GetStartPosition().x + index.x * map.GetTileSize().x + map.GetTileSize().x / 2,
		map.GetStartPosition().y + index.y * map.GetTileSize().y + map.GetTileSize().y / 2 };
	
}

void Player::Draw() {

	int radius = map.GetTileSize().y / 2;

	DrawCircle(
		player_position.x,
		player_position.y,
		radius, 
		YELLOW);

	DrawText(
		TextFormat("%d", moving_count),
		player_position.x-radius + 10,
		player_position.y-radius-20,
		20,
		RED);
	if (time_limit > 2) {
		DrawText(
			TextFormat("3"),
			player_position.x,
			player_position.y,
			20,
			RED);
	}
	else if (time_limit <= 2 && time_limit > 1) {
		DrawText(
			TextFormat("2"),
			player_position.x,
			player_position.y,
			20,
			RED);
	}
	else {
		DrawText(
			TextFormat("1"),
			player_position.x,
			player_position.y,
			20,
			RED);
	}

	
}

void Player::Unload()
{
	moving_count = 10;
	is_moving = true;
}

