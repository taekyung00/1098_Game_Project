#ifndef MAP_H
#define MAP_H

#include <vector>
#include "raylib.h"
#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"

enum class Tile
{
	nothing = 0,
	ground = 1,
	wall = 2/*,
	next_wall = 3*/
};

class Map {

public:
	
	Map(Math::ivec2 index);
	void Load();
	void Update();
	void Draw();
	void Unload();
	Math::ivec2 GetIndex() const{ return index; }
	Math::ivec2 GetExitIndex() const { return exit_index; }
	Math::ivec2 GetStartPosition() const { return start_position; }
	Math::ivec2 GetTileSize() const { return tile_size; }
	Math::ivec2 GetGridSize()const { return grid_size; }
	std::vector<std::vector<Tile>>& GetGrid() { return grid; }

private:
	const Math::ivec2 tile_size = { 40,40 };
	const Math::ivec2 start_position = { 50, 50 };
	std::vector<std::vector<Tile>> grid;

	Math::ivec2 index;
	Math::ivec2 exit_index;
	Math::ivec2 grid_size;

	
	

};

#endif