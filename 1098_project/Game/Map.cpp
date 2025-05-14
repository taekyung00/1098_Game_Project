#include "Map.h"
#include "InGame.h"
#include <random>
#include <algorithm>
#include <filesystem>

void Map::initializestage(Stages _stage)
{
    stage = _stage;
    selectedfiles.clear();
    currentmapindex = 0;
    designPath.clear();

    // stage folder
    std::string folder;
    switch (stage)
    {
    case Stages::stage1: folder = "Game/stage1"; break;
    case Stages::stage2: folder = "Game/stage2"; break;
    case Stages::stage3: folder = "Game/stage3"; break;
    }

    // scan directory
    availablefiles.clear();
    for (auto& entry : std::filesystem::directory_iterator(folder))
    {
        if (entry.path().extension() == ".txt")
        {
            {
                auto stem = entry.path().stem().string();  
                if (stem.size() > 2 && stem.substr(stem.size() - 2) == "_m")
                     continue;
            }
            availablefiles.push_back(entry.path().string());
        }
    }

    // random shuffle
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(availablefiles.begin(), availablefiles.end(), gen);

    // if less then 3 
    size_t count = std::min<size_t>(3, availablefiles.size());
    selectedfiles.assign(availablefiles.begin(), availablefiles.begin() + count);

    designPath = selectedfiles[currentmapindex];
}

Map::Map() :
    current_index_amount({0, 0}), 
    //exit_index(current_index_amount), 
    grid_size(tile_size.x * (Math::ivec2{ current_index_amount } + Math::ivec2{2, 2})),
    stage(Stages::stage1),
    downstairs_rect({ float(start_position.x) + tile_size.x * stairs_index.y + 5, float(start_position.y) + tile_size.x * stairs_index.x + 5, float(tile_size.x) - 10,float(tile_size.y) - 10 })
{   
    // stairmake
    tile_design[stairs_index.x][stairs_index.y].isDownStairs = true;
}

void Map::Load() {
    tile_design.clear();
    spawn_layer.clear();

    std::string temp_string;
    width_amount = 0;
    height_amount = 0;

    std::ifstream file_stream_design;

    if (stage == Stages::stage1) {
        file_stream_design.open(designPath.c_str());
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
                    tile_design[i][j].isBottomEdge = true;
                }
            }
        }
    }
    
    // trapmake
    //tile_design[2][5].isTrap = true;
    //tile_design[2][5].isTrapAlive = true;
    //trap_rect = { static_cast<float>(start_position.x) + tile_size.x * 5 + 5, static_cast<float>(start_position.y) + tile_size.x * 2 +5, static_cast<float>(tile_size.x) - 10,static_cast<float>(tile_size.y)  - 10};
    

    //divide sprite of stage1
    for (int i = 0; i * tile_size.y < sprite.GetTextureSize().y; ++i) {
        for (int j = 0; j * tile_size.x < sprite.GetTextureSize().x; ++j) {
            tiles_numbers.push_back(Math::ivec2{j * tile_size.x, i * tile_size.y});
        }
    }

    current_index_amount = {width_amount, height_amount};

    // current_index = new_index;
    //exit_index = {7, 7};
    grid_size = tile_size.x * (Math::ivec2{ current_index_amount });

    
    Engine::GetWindow().Update(grid_size*2 + 2 * start_position);
    file_stream_design.close();

    std::filesystem::path mapPath{ designPath };
    auto spawnFs = mapPath.parent_path()
        / (mapPath.stem().string() + "_m.txt");
    std::string spawnPath = spawnFs.string();

    std::ifstream spawnStream(spawnPath);
    if (!spawnStream.is_open())
        throw std::runtime_error("fail to open spawn file: " + spawnPath);

    while (std::getline(spawnStream, temp_string)) {
        std::stringstream ss(temp_string);
        std::vector<int> row;
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);
            row.push_back(cell.empty() ? 0 : std::stoi(cell));
        }
        spawn_layer.push_back(std::move(row));
    }
    spawnStream.close();

    //trap_count = trap_max_count;
}

void Map::Update([[maybe_unused]]double dt) {
    
}

void Map::Draw() {
    

    for (int i = 0; i < tile_design.size(); ++i) {
        /*int i = 1;*/
        for (int j = 0; j < tile_design[i].size(); ++j) {
            /*int j = 2;*/
            Math::vec2 position = Math::vec2{static_cast<double>(start_position.x), static_cast<double>(start_position.y)} + Math::vec2{ static_cast<double>(j * tile_size.x), static_cast<double>(i * tile_size.y)};
            // position -= Math::vec2{ double(Engine::GetWindow().GetSize().x), double(Engine::GetWindow().GetSize().y) };
            Rectangle rect = { static_cast<float>(tiles_numbers[tile_design[i][j].tile_number].x), static_cast<float>(tiles_numbers[tile_design[i][j].tile_number].y), static_cast<float>(tile_size.x), static_cast<float>(tile_size.y) };
   
            if (tile_design[i][j].isDownStairs == true) {
                sprite_downstairs.DrawRay(position);
            } else if (tile_design[i][j].tile_number != 0) {
                sprite.Draw(
                    position,
                    rect);
            }
            if (tile_design[i][j].isPawnReachable == true) {
                DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), tile_size.x, tile_size.y, YELLOW);
            }
            if (tile_design[i][j].isRookReachable == true) {
                DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), tile_size.x, tile_size.y, BLUE);
            }
            if (tile_design[i][j].isBishopReachable == true) {
                DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), tile_size.x, tile_size.y, PURPLE);
            }
            DrawText(TextFormat("[%d, %d]", i, j), start_position.x + 5 + j * tile_size.x, start_position.y + 5 + i * tile_size.y, 10, BLACK);
            DrawText(TextFormat("%d", tile_design[i][j].tile_number), start_position.x + 5 + j * tile_size.x, start_position.y + 15 + i * tile_size.y, 10, BLACK);
        }
    }
}

//bool Map::isAble(const Math::ivec2& pos) const {
//    int row = pos.y;
//    int col = pos.x;
//
//    if (row < 0 || row >= 10)
//        return false;
//
//    if (row < 5) {
//        if (col < 0 || col >= 10)
//            return false;
//    } else {
//        if (col < 5 || col >= 10)
//            return false;
//    }
//
//    return true;
//}

void Map::Unload() {

}
