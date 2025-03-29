#include "Map.h"
Map::Map(Math::ivec2 index) : index(index) , exit_index(index){}

void Map::Load() {
	if (grid.size() < ((index.x + 2) * (index.y + 2))) {
		grid.resize((index.x + 2) * (index.y + 2));
	}
	

	for (int i = 0; i < index.y + 2; ++i) {
		for (int j = 0; j < index.x + 2; ++j) {
			grid[i].push_back(Tile::nothing);
		}
	}

	for (int i = 0; i < index.x + 2; i++) {
		grid[0][i] = Tile::wall;
	}

	for (int i = 0; i < index.x + 2; i++) {
		grid[index.y + 1][i] = Tile::wall;
	}

	for (int i = 0; i < index.y + 2; i++) {
		grid[i][0] = Tile::wall;
	}

	for (int i = 0; i < index.y + 2; i++) {
		grid[i][index.x + 1] = Tile::wall;
	}

	for (int i = 1; i < index.y + 1; i++) {
		for (int j = 1; j < index.x + 1; j++) {
			grid[i][j] = Tile::ground;
		}
	}
}

void Map::Update() {

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

void Map::Unload()
{
	grid.clear();
}
