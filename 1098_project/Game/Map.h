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
	void Load(Math::ivec2 index);
	void Update(const Math::ivec2& new_index);
	void Draw();
	void Unload();
	Math::ivec2 GetCurrentIndex() const{ return current_index; }
	Math::ivec2 GetExitIndex() const { return exit_index; }
	Math::ivec2 GetStartPosition() const { return start_position; }
	Math::ivec2 GetTileSize() const { return tile_size; }
	Math::ivec2 GetGridSize()const { return grid_size; }
	std::vector<std::vector<Tile>>& GetGrid() { return grid; }

private:

	const Math::ivec2 tile_size = { 40,40 };
	const Math::ivec2 start_position = { 50, 50 };
	std::vector<std::vector<Tile>> grid;

	Math::ivec2 current_index;
	Math::ivec2 exit_index;
	Math::ivec2 grid_size;
	
	std::vector<std::string> stage1_tile_paths = {
		"Assets/Stage_1_32_tile1_1.png",
		"Assets/Stage_1_32_tile1_2.png",
		"Assets/Stage_1_32_tile1_3.png",
		"Assets/Stage_1_32_tile1_4.png",
		"Assets/Stage_1_32_tile1_5.png",
		"Assets/Stage_1_32_tile1_6.png",
		"Assets/Stage_1_32_tile1_7.png",
		"Assets/Stage_1_32_tile1_8.png",
		"Assets/Stage_1_32_tile1_9.png"
	};

	std::vector<std::string> stage1_wall_paths = {
		"Assets/Stage_1_32_wall1_Corner.png",
		"Assets/Stage_1_32_wall1_Plain.png"
	};


	
	

};

#endif