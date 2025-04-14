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

enum class TileState {
    nothing = 0,
    ground = 1,
    wall = 2 /*,
     next_wall = 3*/
};

enum class Stages {
    stage1,
    stage2
};

struct Tile {
    int tile_number = 0;
    bool isRightEdge = false;
    bool isLeftEdge = false;
    bool isTopEdge = false;
    bool isBotttomEdge = false;
    bool isUpStairs = false;
    bool isDownStairs = false;
    bool isTrap = false;
    bool isTrapAlive = false;
};

class Map {
   public:
    Map();
    void Load();
    void Update(double dt);
    void Draw();
    void Unload();
    Math::ivec2 GetCurrentIndex() const { return current_index; }
    Math::ivec2 GetExitIndex() const { return exit_index; }
    Math::ivec2 GetStartPosition() const { return start_position; }
    Math::ivec2 GetTileSize() const { return tile_size; }
    Math::ivec2 GetGridSize() const { return grid_size; }
    std::vector<std::vector<TileState>>& GetGrid() { return grid; }
    std::vector<std::vector<Tile>>& GetTileDesign() { return tile_design; }
    bool isAble(const Math::ivec2& pos) const;
    Stages GetCurrentStage() const { return stages; }
    Rectangle& GetTrapRect()  { return trap_rect; }
    Rectangle& GetDownStairsRect()  { return downstairs_rect; }
    std::vector<Math::ivec2>& GetTileNumber(){ return tiles_numbers; }

   private:
    CS230::Sprite sprite;
    //temporary
    CS230::Sprite sprite_trap_dead;
    CS230::Sprite sprite_trap_alive;
    CS230::Sprite sprite_downstairs;

    const Math::ivec2 tile_size = {32, 32};
    const Math::ivec2 start_position = {50, 50};
    std::vector<std::vector<TileState>> grid;

    Math::ivec2 current_index;
    Math::ivec2 exit_index;
    Math::ivec2 grid_size;

    

    Stages stages = Stages::stage1;

    std::vector<Math::ivec2> tiles_numbers;

    std::ifstream file_stream_design;

    const char* stage1_design_path = "Game/stage1_tiles.txt";

    

    std::vector<std::vector<Tile>> tile_design;

    int width_amount = 0;
    int height_amount = 0;

    const double trap_max_count = 1.0;
    double trap_count = 1.0;

    Rectangle trap_rect;
    Rectangle downstairs_rect;

    
};

#endif