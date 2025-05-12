#include "Map.h"
#include "InGame.h"


Map::Map() : 
    current_index_amount({0, 0}), 
    exit_index(current_index_amount), 
    grid_size(tile_size.x * (Math::ivec2{ current_index_amount } + Math::ivec2{2, 2})),
    stage(Stages::stage1)
{}

void Map::Load() {
    tile_design.clear();
    std::string temp_string;
    width_amount = 0;
    height_amount = 0;

    std::ifstream file_stream_design;

    if (stage == Stages::stage1) {
        file_stream_design.open(stage1_design_path);
        if (file_stream_design.is_open() == false) {
            throw std::runtime_error("fail to open in stage " + std::to_string(static_cast<int>(Stages::stage1)));
        }
        std::getline(file_stream_design, temp_string);
        if (temp_string.size()==0) {
            throw std::runtime_error("fail to open sprite in stage " + std::to_string(static_cast<int>(Stages::stage1)));
        }
        sprite.Load(temp_string, {0, 0});
    }

    /*sprite_trap_alive.Load("Assets/sprite_trap_alive.png",{0,0});
    sprite_trap_dead.Load("Assets/sprite_trap_dead.png",{0,0});*/
    sprite_downstairs.Load("Assets/sprite_downstairs.png",{0,0});

    tiles_numbers.clear();
    tiles_numbers.push_back({-1, -1});  // for nothing, [0]
    temp_string.clear();

    while (std::getline(file_stream_design, temp_string)) {
        std::stringstream string_stream = std::stringstream(temp_string);
        temp_string.clear();
        std::vector<Tile> row;

        int temp_width = 0;
        while (std::getline(string_stream, temp_string, ',')) {
            //erase tap or whitespace before num
            temp_string.erase(0, temp_string.find_first_not_of(" \t"));
            //erase tap or whitespace after num
            temp_string.erase(temp_string.find_last_not_of(" \t") + 1);

            if (!temp_string.empty()) {
                row.push_back({std::stoi(temp_string)});
                temp_width++;
            }
        }

        if (temp_width > width_amount) {
            width_amount = temp_width;
        }
        ++height_amount;
        tile_design.push_back(row);
    }

    // tilecheck - hardcoded for stage1
    if (stage == Stages::stage1) {
        for (int i = 0; i < tile_design.size(); ++i) {
            for (int j = 0; j < tile_design[i].size(); ++j) {
                // edge check
                if (tile_design[i][j].tile_number == 1 ||
                    tile_design[i][j].tile_number == 4 ||
                    tile_design[i][j].tile_number == 9 ||
                    tile_design[i][j].tile_number == 12 ||
                    tile_design[i][j].tile_number == 17 ||
                    tile_design[i][j].tile_number == 20) {
                    tile_design[i][j].isLeftEdge = true;
                }

                if (
                    tile_design[i][j].tile_number == 3 ||
                    tile_design[i][j].tile_number == 6 ||
                    tile_design[i][j].tile_number == 11 ||
                    tile_design[i][j].tile_number == 14 ||
                    tile_design[i][j].tile_number == 19 ||
                    tile_design[i][j].tile_number == 22) {
                    tile_design[i][j].isRightEdge = true;
                }
                if (
                    tile_design[i][j].tile_number == 1 ||
                    tile_design[i][j].tile_number == 2 ||
                    tile_design[i][j].tile_number == 3 ||
                    tile_design[i][j].tile_number == 4 ||
                    tile_design[i][j].tile_number == 5 ||
                    tile_design[i][j].tile_number == 6) {
                    tile_design[i][j].isTopEdge = true;
                }
                if (
                    tile_design[i][j].tile_number == 17 ||
                    tile_design[i][j].tile_number == 18 ||
                    tile_design[i][j].tile_number == 19 ||
                    tile_design[i][j].tile_number == 20 ||
                    tile_design[i][j].tile_number == 21 ||
                    tile_design[i][j].tile_number == 22) {
                    tile_design[i][j].isBotttomEdge = true;
                }
            }
        }
    }
    
    // trapmake
    //tile_design[2][5].isTrap = true;
    //tile_design[2][5].isTrapAlive = true;
    //trap_rect = { static_cast<float>(start_position.x) + tile_size.x * 5 + 5, static_cast<float>(start_position.y) + tile_size.x * 2 +5, static_cast<float>(tile_size.x) - 10,static_cast<float>(tile_size.y)  - 10};
    // stairmake
    tile_design[7][7].isDownStairs = true;
    downstairs_rect = { float(start_position.x) + tile_size.x * 7 + 5, float(start_position.y) + tile_size.x * 7 + 5, float(tile_size.x) - 10,float(tile_size.y) - 10 };

    //divide sprite of stage1
    for (int i = 0; i * tile_size.y < sprite.GetTextureSize().y; ++i) {
        for (int j = 0; j * tile_size.x < sprite.GetTextureSize().x; ++j) {
            tiles_numbers.push_back(Math::ivec2{j * tile_size.x, i * tile_size.y});
        }
    }

    current_index_amount = {width_amount, height_amount};

    // current_index = new_index;
    exit_index = {7, 7};
    grid_size = tile_size.x * (Math::ivec2{ current_index_amount });

    
    Engine::GetWindow().Update(grid_size*2 + 2 * start_position);
    file_stream_design.close();
    //trap_count = trap_max_count;
}

void Map::Update([[maybe_unused]]double dt) {
    //trap_count -= dt;
    //if (trap_count <= 0.0) {
    //    //hardcoded index
    //    if (tile_design[2][5].isTrapAlive == true) {
    //        tile_design[2][5].isTrapAlive = false;
    //    }
    //    else {
    //        tile_design[2][5].isTrapAlive = true;
    //    }
    //    
    //    trap_count = trap_max_count;
    //}
}

void Map::Draw() {
    

    for (int i = 0; i < tile_design.size(); ++i) {
        /*int i = 1;*/
        for (int j = 0; j < tile_design[i].size(); ++j) {
            /*int j = 2;*/
            Math::vec2 position = Math::vec2{static_cast<double>(start_position.x), static_cast<double>(start_position.y)} + Math::vec2{ static_cast<double>(j * tile_size.x), static_cast<double>(i * tile_size.y)};
            // position -= Math::vec2{ double(Engine::GetWindow().GetSize().x), double(Engine::GetWindow().GetSize().y) };
            Rectangle rect = { static_cast<float>(tiles_numbers[tile_design[i][j].tile_number].x), static_cast<float>(tiles_numbers[tile_design[i][j].tile_number].y), static_cast<float>(tile_size.x), static_cast<float>(tile_size.y) };
            //if (tile_design[i][j].isTrap == true) {
            //    if (tile_design[i][j].isTrapAlive == true) {
            //        //use temp_rect for using raylib_based sprite.draw
            //        sprite_trap_alive.DrawRay(position);
            //    }
            //    else {
            //        sprite_trap_dead.DrawRay(position);
            //    }
            //} 
            if (tile_design[i][j].isDownStairs == true) {
                sprite_downstairs.DrawRay(position);
            } else if (tile_design[i][j].tile_number != 0) {
                sprite.Draw(
                    position,
                    rect);
            }
            DrawText(TextFormat("[%d, %d]", i, j), start_position.x + 5 + j * tile_size.x, start_position.y + 5 + i * tile_size.y, 10, BLACK);
            DrawText(TextFormat("%d", tile_design[i][j].tile_number), start_position.x + 5 + j * tile_size.x, start_position.y + 15 + i * tile_size.y, 10, BLACK);
        }
    }
}

bool Map::isAble(const Math::ivec2& pos) const {
    int row = pos.y;
    int col = pos.x;

    if (row < 0 || row >= 10)
        return false;

    if (row < 5) {
        if (col < 0 || col >= 10)
            return false;
    } else {
        if (col < 5 || col >= 10)
            return false;
    }

    return true;
}

void Map::Unload() {
    //grid.clear();
}
