#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "raylib.h"

enum class Tile {
    nothing = 0,
    ground = 1,
    wall = 2 /*,
     next_wall = 3*/
};

class Map {
   public:
    Map(Math::ivec2 index);
    void Load(Math::ivec2 index);
    void Update(const Math::ivec2& new_index);
    void Draw();
    void Unload();
    Math::ivec2 GetCurrentIndex() const { return current_index; }
    Math::ivec2 GetExitIndex() const { return exit_index; }
    Math::ivec2 GetStartPosition() const { return start_position; }
    Math::ivec2 GetTileSize() const { return tile_size; }
    Math::ivec2 GetGridSize() const { return grid_size; }
    std::vector<std::vector<Tile>>& GetGrid() { return grid; }
    std::vector<std::vector<int>>& GetTileDesign() { return tile_design; }
    bool isAble(const Math::ivec2& pos) const;

   private:
    CS230::Sprite sprite;

    const Math::ivec2 tile_size = {32, 32};
    const Math::ivec2 start_position = {50, 50};
    std::vector<std::vector<Tile>> grid;

    Math::ivec2 current_index;
    Math::ivec2 exit_index;
    Math::ivec2 grid_size;

    enum class stages {
        stage1
    };

    stages stages = stages::stage1;

    std::vector<Math::ivec2> tiles_numbers;

    std::ifstream file_stream_design;

    const char* stage1_design_path = "Game/stage1_tiles.txt";

    std::vector<std::vector<int>> tile_design;

    int width_amount = 0;
    int height_amount = 0;
};

#endif