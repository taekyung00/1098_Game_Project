#ifndef MAP_H
#define MAP_H
#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <raylib.h>

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"



//enum class TileState {
//    nothing = 0,
//    ground = 1,
//    wall = 2 /*,
//     next_wall = 3*/
//};

extern const Math::ivec2 start_position ;
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
    //bool isTrap = false;
    //bool isTrapAlive = false;
};



class Map {
   public:
    Map();
    void Load();
    void Update(double dt);
    void Draw();
    void Unload();
    
    //Math::ivec2 GetCurrentIndex() const { return current_index; }
    //Math::ivec2 GetTileSize() const { return tile_size; }
    //std::vector<std::vector<TileState>>& GetGrid() { return grid; }
    //const Rectangle& GetTrapRect()  const { return trap_rect; }

    const Math::ivec2& GetExitIndex() const { return exit_index; }
    const Math::ivec2& GetStartPosition() const { return start_position; }    
    const Math::ivec2& GetGridSize() const { return grid_size; }    
    const std::vector<std::vector<Tile>>& GetTileDesign() { return tile_design; }
    bool isAble(const Math::ivec2& pos) const;
    const Stages& GetCurrentStage() const { return stage; }    
    const Rectangle& GetDownStairsRect()  const { return downstairs_rect; }
    const std::vector<Math::ivec2>& GetTileNumber() const { return tiles_numbers; }

   private:
    CS230::Sprite sprite;
    CS230::Sprite sprite_downstairs;

    Math::ivec2 current_index_amount;
    Math::ivec2 exit_index;
    Math::ivec2 grid_size;

    Stages stage = Stages::stage1;

    std::vector<Math::ivec2> tiles_numbers;

    const char* stage1_design_path = "Game/stage1_tiles.txt";

    std::vector<std::vector<Tile>> tile_design;

    int width_amount = 0;
    int height_amount = 0;

    Rectangle downstairs_rect;

    //temporary
    /*CS230::Sprite sprite_trap_dead;
    CS230::Sprite sprite_trap_alive;*/
    //std::vector<std::vector<TileState>> grid;
    /*const double trap_max_count = 1.0;
    double trap_count = 1.0;*/
    //Rectangle trap_rect;

    
};

#endif