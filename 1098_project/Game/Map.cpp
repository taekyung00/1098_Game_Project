#include "Map.h"
#include "InGame.h"
#include <random>
#include <algorithm>

Map::Map() : 
    current_index_amount({0, 0}), 
    exit_index(current_index_amount), 
    grid_size(tile_size.x * (Math::ivec2{ current_index_amount } + Math::ivec2{2, 2})),
    stage(Stages::stage1)
{}

void Map::initializestage(Stages stage)
{
    currentStage = stage;
    selectedfiles.clear();
    currentmapindex = 0;

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
    Loadfile(selectedfiles[currentmapindex]);
}

void Map::Loadfile(const std::string& designPath) {
    tile_design.clear();
    width_amount = 0;
    height_amount = 0;

    std::ifstream file_stream(designPath);
    if (!file_stream.is_open())
        throw std::runtime_error("fail to open map file: " + designPath);

    std::string line;
    // 첫 줄(스프라이트 경로)은 이미 Load()에서 처리했으므로 건너뛰기
    std::getline(file_stream, line);

    // 남은 라인들 CSV 파싱
    while (std::getline(file_stream, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<Tile> row;
        int tempW = 0;

        while (std::getline(ss, cell, ',')) {
            // 앞뒤 공백 제거
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);

            if (!cell.empty()) {
                row.push_back({ std::stoi(cell) });
                ++tempW;
            }
        }

        width_amount = std::max(width_amount, tempW);
        ++height_amount;
        tile_design.push_back(row);
    }

    file_stream.close();

    // 에지 플래그 설정 (stage1 전용)
    if (stage == Stages::stage1) {
        for (int i = 0; i < tile_design.size(); ++i) {
            for (int j = 0; j < tile_design[i].size(); ++j) {
                int t = tile_design[i][j].tile_number;
                if (t == 1 || t == 4 || t == 9 || t == 12 || t == 17 || t == 20)
                    tile_design[i][j].isLeftEdge = true;
                if (t == 3 || t == 6 || t == 11 || t == 14 || t == 19 || t == 22)
                    tile_design[i][j].isRightEdge = true;
                if (t >= 1 && t <= 6)
                    tile_design[i][j].isTopEdge = true;
                if (t >= 17 && t <= 22)
                    tile_design[i][j].isBotttomEdge = true;
            }
        }
    }

    // trap logic place holder
}

void Map::Load() {
    // 1) 타일셋 스프라이트 로드
    if (stage == Stages::stage1) {
        std::ifstream tmp(designPath);
        std::string spritePath;
        std::getline(tmp, spritePath);
        tmp.close();
        sprite.Load(spritePath, { 0,0 });
    }
    sprite_downstairs.Load("Assets/sprite_downstairs.png", { 0,0 });

    // 2) CSV 파싱 분리
    Loadfile(designPath);

    tiles_numbers.clear();
    tiles_numbers.push_back({ -1, -1 });  // index 0 더미

    // sprite.GetTextureSize() 로부터 행·열 개수만큼 cell 좌표 계산
    for (int i = 0; i * tile_size.y < sprite.GetTextureSize().y; ++i) {
        for (int j = 0; j * tile_size.x < sprite.GetTextureSize().x; ++j) {
            tiles_numbers.push_back({ j * tile_size.x, i * tile_size.y });
        }
    }

    // 3) 계단 강제 배치
    if (!tile_design.empty() && tile_design[0].size() > 2) {
        tile_design[0][2].isDownStairs = true;
        exit_index = { 2, 0 };
    }

    // 4) 인덱스/그리드 계산 & 윈도우 업데이트
    current_index_amount = { width_amount, height_amount };
    grid_size = tile_size.x * current_index_amount;
    Engine::GetWindow().Update(grid_size * 2 + 2 * start_position);
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

    if (row < 0 || row >= width_amount)
        return false;

    if (row < 5) {
        if (col < 0 || col >= height_amount)
            return false;
    } else {
        if (col < height_amount || col >= height_amount)
            return false;
    }

    return true;
}

void Map::Unload() {
    //grid.clear();
}

void Map::Update(double dt) {
    // …
}
