#include "Map.h"
Map::Map(Math::ivec2 current_index) : current_index(current_index), exit_index(current_index), grid_size(tile_size.x* (Math::ivec2{ current_index } + Math::ivec2{ 2,2 })) {}

void Map::Load(Math::ivec2 new_index) {

	current_index = new_index;
	exit_index = current_index;
	grid_size = tile_size.x * (Math::ivec2{ current_index } + Math::ivec2{ 2,2 });
	if (grid.size() < ((current_index.x + 2) * (current_index.y + 2))) {
		grid.resize((current_index.x + 2) * (current_index.y + 2));
	}


	for (int i = 0; i < current_index.y + 2; ++i) {
		for (int j = 0; j < current_index.x + 2; ++j) {
			grid[i].push_back(Tile::nothing);
		}
	}

	for (int i = 0; i < current_index.x + 2; i++) {
		grid[0][i] = Tile::wall;
	}

	for (int i = 0; i < current_index.x + 2; i++) {
		grid[current_index.y + 1][i] = Tile::wall;
	}

	for (int i = 0; i < current_index.y + 2; i++) {
		grid[i][0] = Tile::wall;
	}

	for (int i = 0; i < current_index.y + 2; i++) {
		grid[i][current_index.x + 1] = Tile::wall;
	}

	for (int i = 1; i < current_index.y + 1; i++) {
		for (int j = 1; j < current_index.x + 1; j++) {
			grid[i][j] = Tile::ground;
		}
	}
	Engine::GetWindow().Update(grid_size + 2 * start_position);
}

void Map::Update(const Math::ivec2& new_index) {
	if (current_index != new_index) {
		current_index = new_index;
	}
}

void Map::Draw() {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			switch (grid[i][j])
			{
			case Tile::nothing:
				DrawRectangle(start_position.x + j * tile_size.x, start_position.y + i * tile_size.y, tile_size.x, tile_size.y, WHITE);

				break;
			case Tile::ground:
				DrawRectangle(start_position.x + j * tile_size.x, start_position.y + i * tile_size.y, tile_size.x, tile_size.y, BROWN);
				break;
			case Tile::wall:
				DrawRectangle(start_position.x + j * tile_size.x, start_position.y + i * tile_size.y, tile_size.x, tile_size.y, PURPLE);
				break;
			}
			DrawText(TextFormat("[%d, %d]", i, j), start_position.x + 5 + j * tile_size.x, start_position.y + 5 + i * tile_size.y, 10, BLACK);
			DrawRectangleLines(start_position.x + j * tile_size.x, start_position.y + i * tile_size.y, tile_size.x, tile_size.y, BLACK);
		}
	}
}
	
bool Map::isAble(const Math::ivec2& pos) const {
	if (pos.y < 0|| pos.y >= grid.size() || pos.x < 0 || pos.x >= grid[0].size()) {
		return false;
	}
	return grid[pos.x][pos.y] == Tile::ground;
}

void Map::Unload()
{
	grid.clear();
}
