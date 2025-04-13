#include "Map.h"
Map::Map() : current_index({0, 0}), exit_index(current_index), grid_size(tile_size.x * (Math::ivec2{current_index} + Math::ivec2{2, 2})) {}

void Map::Load() {
    tile_design.clear();
    std::string temp_string;
    width_amount = 0;
    height_amount = 0;

    if (stages == Stages::stage1) {
        file_stream_design.open(stage1_design_path);
        if (file_stream_design.is_open() == false) {
            throw std::runtime_error("fail to open in stage 1");
        }
        std::getline(file_stream_design, temp_string);
        sprite.Load(temp_string, {0, 0});
    }
    sprite_trap_alive.Load("Assets/sprite_trap_alive.png",{0,0});
    sprite_trap_dead.Load("Assets/sprite_trap_dead.png",{0,0});
    sprite_downstairs.Load("Assets/sprite_downstairs.png",{0,0});

    tiles_numbers.clear();
    tiles_numbers.push_back({-1, -1});  // for nothing, [0]

    while (std::getline(file_stream_design, temp_string)) {
        std::stringstream string_stream = std::stringstream(temp_string);
        temp_string.clear();
        std::vector<Tile> row;

        int temp_width = 0;
        while (std::getline(string_stream, temp_string, ',')) {
            temp_string.erase(0, temp_string.find_first_not_of(" \t"));
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
    // trapmake
    tile_design[2][5].isTrap = true;
    tile_design[2][5].isTrapAlive = true;
    // stairmake
    tile_design[7][7].isDownStairs = true;

    for (int i = 0; i * tile_size.y < sprite.GetTextureSize().y; ++i) {
        for (int j = 0; j * tile_size.x < sprite.GetTextureSize().x; ++j) {
            tiles_numbers.push_back(Math::ivec2{j * tile_size.x, i * tile_size.y});
        }
    }

    current_index = {width_amount, height_amount};

    // current_index = new_index;
    exit_index = {7, 7};
    grid_size = tile_size.x * (Math::ivec2{current_index});

    /*for (int i = 0; i < current_index.y ; ++i) {
            std::vector<Tile> row;
            for (int j = 0; j < current_index.x ; ++j) {
                    switch (tile_design[i][j])
                    {
                    case 1:
                            row.push_back(Tile::wall);
                            break;
                    case 2:
                            row.push_back(Tile::wall);
                            break;
                    case 3:
                            row.push_back(Tile::wall);
                            break;
                    case 4:
                            row.push_back(Tile::wall);
                            break;
                    case 5:
                            row.push_back(Tile::wall);
                            break;
                    case 6:
                            row.push_back(Tile::wall);
                            break;
                    case 9:
                            row.push_back(Tile::wall);
                            break;
                    case 11:
                            row.push_back(Tile::wall);
                    case 12:
                            row.push_back(Tile::wall);
                            break;
                    case 14:
                            row.push_back(Tile::wall);
                            break;
                    case 17:
                            row.push_back(Tile::wall);
                            break;
                    case 18:
                            row.push_back(Tile::wall);
                            break;
                    case 19:
                            row.push_back(Tile::wall);
                            break;
                    case 20:
                            row.push_back(Tile::wall);
                            break;
                    case 21:
                            row.push_back(Tile::wall);
                            break;
                    case 22:
                            row.push_back(Tile::wall);
                            break;
                    case 0:
                            row.push_back(Tile::nothing);
                            break;
                    default:
                            row.push_back(Tile::ground);
                            break;
                    }
            }
            grid.push_back(row);
    }*/

    /*for (int i = 0; i < current_index.x + 2; i++) {
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
    }*/
    Engine::GetWindow().Update(grid_size + 2 * start_position);
    file_stream_design.close();
    trap_max_count = 1.0;
}

void Map::Update(double dt) {
    trap_max_count -= dt;
    if (trap_max_count <= 0.0) {
        //hardcoded index
        if (tile_design[2][5].isTrapAlive == true) {
            tile_design[2][5].isTrapAlive = false;
        }
        else {
            tile_design[2][5].isTrapAlive = true;
        }

    }
}

void Map::Draw() {
    /*for (int i = 0; i < grid.size(); ++i) {
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
    }*/

    for (int i = 0; i < tile_design.size(); ++i) {
        /*int i = 1;*/
        for (int j = 0; j < tile_design[i].size(); ++j) {
            /*int j = 2;*/
            Math::vec2 position = Math::vec2{double(start_position.x), double(start_position.y)} + Math::vec2{double(j * tile_size.x), double(i * tile_size.y)};
            // position -= Math::vec2{ double(Engine::GetWindow().GetSize().x), double(Engine::GetWindow().GetSize().y) };
            Rectangle rect = {tiles_numbers[tile_design[i][j].tile_number].x, tiles_numbers[tile_design[i][j].tile_number].y, tile_size.x, tile_size.y};
            if (tile_design[i][j].isTrap == true) {
                if (tile_design[i][j].isTrapAlive == true) {
                    //use temp_rect for using raylib_based sprite.draw
                    Rectangle temp_rect = { position.x,position.y,tile_size.x,tile_size.y };
                    sprite_trap_alive.Draw(position, temp_rect);
                }
                else {
                    Rectangle temp_rect = { position.x,position.y,tile_size.x,tile_size.y };
                    sprite_trap_dead.Draw(position, temp_rect);
                }
                DrawRectangle(position.x, position.y, rect.width, rect.height, BROWN);
            } else if (tile_design[i][j].isDownStairs == true) {
                Rectangle temp_rect = { position.x,position.y,tile_size.x,tile_size.y };
                sprite_downstairs.Draw(position, temp_rect);
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
    grid.clear();
}
