#include "Map.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Merchant.h"

void Map::InitializeStage(Stages _stage)
{
    stage = _stage;
    selectedfiles.clear();
    currentmapindex = 0;
    designPath.clear();

    //make designpath
    if (room == Rooms::Store) {
        designPath = "Assets/LevelDesign/store/s.txt";
        initialize_store();
    }
    else if (stage == Stages::Tutorial) {
        switch (room)
        {
        case Rooms::Room1:
            designPath = "Assets/LevelDesign/tutorial/1.txt";
            break;
        case Rooms::Room2:
            designPath = "Assets/LevelDesign/tutorial/2.txt";
            break;
        case Rooms::Room3:
            designPath = "Assets/LevelDesign/tutorial/3.txt";
            break;
        case Rooms::Room4:
            designPath = "Assets/LevelDesign/tutorial/4.txt";
            break;
        case Rooms::Room5:
            designPath = "Assets/LevelDesign/tutorial/5.txt";
            break;
        case Rooms::Room6:
            designPath = "Assets/LevelDesign/tutorial/6.txt";
            break;
        }
    }
    else if (stage == Stages::Boss) {
        switch (room)
        {
        case Rooms::Room1:
            designPath = "Assets/LevelDesign/Boss/1.txt";
            break;
        case Rooms::Room2:
            designPath = "Assets/LevelDesign/Boss/2.txt";
            break;
        case Rooms::Room3:
            designPath = "Assets/LevelDesign/Boss/3.txt";
            break;
        }
    }
    else {
        std::string folder;

        switch (stage)
        {
            //case Stages::Tutorial: 
        case Stages::stage1: folder = "Assets/LevelDesign/stage1"; break;
        case Stages::stage2: folder = "Assets/LevelDesign/stage2"; break;
        case Stages::stage3: folder = "Assets/LevelDesign/stage3"; break;            
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
                    if (stem.size() > 2 && stem.substr(stem.size() - 2) == "_t")
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
    
    //designPath = designPath = "Game/stage1/4.txt";
    Engine::GetLogger().LogDebug(designPath.c_str());

    tile_design.clear();
    //spawn_layer.clear();
    //spawn_trap_layer.clear();

    std::string temp_string;
    width_amount = 0;
    height_amount = 0;

    std::ifstream file_stream_design;

    file_stream_design.open(designPath.c_str());
    if (file_stream_design.is_open() == false) {
        throw std::runtime_error("fail to open in stage " + std::to_string(static_cast<int>(Stages::stage1)));
    }
    //sprite_downstairs.Load("Assets/sprite_downstairs.png", { 0,0 });

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
                row.push_back({ std::stoi(temp_string) });
                temp_width++;
            }
        }

        if (temp_width > width_amount) {
            width_amount = temp_width;
        }
        ++height_amount;
        tile_design.push_back(row);
    }
    //tile_design flip! - to use [0,0] as bottom-left

    for (int i = 0; i < (tile_design.size() - 1) / 2; ++i) {
        for (int j = 0; j < tile_design[i].size(); ++j) {
            int temp = tile_design[i][j].tile_number;
            tile_design[i][j].tile_number = tile_design[tile_design.size() - 1 - i][j].tile_number;
            tile_design[tile_design.size() - 1 - i][j].tile_number = temp;
        }
    }

    for (int i = 0; i < tile_design.size(); ++i) {
        for (int j = i; j < tile_design[i].size(); ++j) {
            int temp = tile_design[i][j].tile_number;
            tile_design[i][j].tile_number = tile_design[j][i].tile_number;
            tile_design[j][i].tile_number = temp;
        }

    }
    height_amount = static_cast<int>(tile_design.size());
    width_amount = static_cast<int>(tile_design[0].size());
    // tilecheck - hardcoded
    for (int i = 0; i < tile_design.size(); ++i) {
        for (int j = 0; j < tile_design[i].size(); ++j) {
            // edge check
            if (tile_design[i][j].tile_number == 1 ||
                tile_design[i][j].tile_number == 4 ||
                tile_design[i][j].tile_number == 7 ||
                tile_design[i][j].tile_number == 10 ||
                tile_design[i][j].tile_number == 13 ||
                tile_design[i][j].tile_number == 16 ||
                tile_design[i][j].tile_number == 19 ||
                tile_design[i][j].tile_number == 22 ||
                tile_design[i][j].tile_number == 25 ||
                tile_design[i][j].tile_number == 28 ||
                tile_design[i][j].tile_number == 31 ||
                tile_design[i][j].tile_number == 34 ||
                tile_design[i][j].tile_number == 37 ||
                tile_design[i][j].tile_number == 40 ||
                tile_design[i][j].tile_number == 43 ||
                tile_design[i][j].tile_number == 46 ||
                tile_design[i][j].tile_number == 49 ||
                tile_design[i][j].tile_number == 52 ||
                tile_design[i][j].tile_number == 55 ||
                tile_design[i][j].tile_number == 58 ||
                tile_design[i][j].tile_number == 61 ||
                tile_design[i][j].tile_number == 64 ||
                tile_design[i][j].tile_number == 67 ||
                tile_design[i][j].tile_number == 70) {
                tile_design[i][j].isLeftEdge = true;
            }

            if (
                tile_design[i][j].tile_number == 3 ||
                tile_design[i][j].tile_number == 6 ||
                tile_design[i][j].tile_number == 9 ||
                tile_design[i][j].tile_number == 12 ||
                tile_design[i][j].tile_number == 15 ||
                tile_design[i][j].tile_number == 18 ||
                tile_design[i][j].tile_number == 21 ||
                tile_design[i][j].tile_number == 24 ||
                tile_design[i][j].tile_number == 27 ||
                tile_design[i][j].tile_number == 30 ||
                tile_design[i][j].tile_number == 33 ||
                tile_design[i][j].tile_number == 36 ||
                tile_design[i][j].tile_number == 39 ||
                tile_design[i][j].tile_number == 42 ||
                tile_design[i][j].tile_number == 45 ||
                tile_design[i][j].tile_number == 48 ||
                tile_design[i][j].tile_number == 51 ||
                tile_design[i][j].tile_number == 54 ||
                tile_design[i][j].tile_number == 57 ||
                tile_design[i][j].tile_number == 60 ||
                tile_design[i][j].tile_number == 63 ||
                tile_design[i][j].tile_number == 66 ||
                tile_design[i][j].tile_number == 69 ||
                tile_design[i][j].tile_number == 72) {
                tile_design[i][j].isRightEdge = true;
            }
            if (
                tile_design[i][j].tile_number == 1 ||
                tile_design[i][j].tile_number == 2 ||
                tile_design[i][j].tile_number == 3 ||
                tile_design[i][j].tile_number == 4 ||
                tile_design[i][j].tile_number == 5 ||
                tile_design[i][j].tile_number == 6 ||
                tile_design[i][j].tile_number == 19 ||
                tile_design[i][j].tile_number == 20 ||
                tile_design[i][j].tile_number == 21 ||
                tile_design[i][j].tile_number == 22 ||
                tile_design[i][j].tile_number == 23 ||
                tile_design[i][j].tile_number == 24 ||
                tile_design[i][j].tile_number == 37 ||
                tile_design[i][j].tile_number == 38 ||
                tile_design[i][j].tile_number == 39 ||
                tile_design[i][j].tile_number == 40 ||
                tile_design[i][j].tile_number == 41 ||
                tile_design[i][j].tile_number == 42 ||
                tile_design[i][j].tile_number == 55 ||
                tile_design[i][j].tile_number == 56 ||
                tile_design[i][j].tile_number == 57 ||
                tile_design[i][j].tile_number == 58 ||
                tile_design[i][j].tile_number == 59 ||
                tile_design[i][j].tile_number == 60) {
                tile_design[i][j].isTopEdge = true;
            }
            if (
                tile_design[i][j].tile_number == 13 ||
                tile_design[i][j].tile_number == 14 ||
                tile_design[i][j].tile_number == 15 ||
                tile_design[i][j].tile_number == 16 ||
                tile_design[i][j].tile_number == 17 ||
                tile_design[i][j].tile_number == 18 ||
                tile_design[i][j].tile_number == 31 ||
                tile_design[i][j].tile_number == 32 ||
                tile_design[i][j].tile_number == 33 ||
                tile_design[i][j].tile_number == 34 ||
                tile_design[i][j].tile_number == 35 ||
                tile_design[i][j].tile_number == 36 ||
                tile_design[i][j].tile_number == 49 ||
                tile_design[i][j].tile_number == 50 ||
                tile_design[i][j].tile_number == 51 ||
                tile_design[i][j].tile_number == 52 ||
                tile_design[i][j].tile_number == 53 ||
                tile_design[i][j].tile_number == 54 ||
                tile_design[i][j].tile_number == 67 ||
                tile_design[i][j].tile_number == 68 ||
                tile_design[i][j].tile_number == 69 ||
                tile_design[i][j].tile_number == 70 ||
                tile_design[i][j].tile_number == 71 ||
                tile_design[i][j].tile_number == 72) {
                tile_design[i][j].isBottomEdge = true;
            }
        }
    }

    current_index_amount = { width_amount, height_amount };
    grid_size = tile_size.x * (Math::ivec2{ current_index_amount });

    file_stream_design.close();
}


void Map::ClearEnemiesReachable()
{
    for (int j = 0; j < tile_design.size(); ++j) {
        for (int i = 0; i < tile_design[j].size(); ++i) {
            tile_design[j][i].isEnemyReachable = false;
        }
    }
}

void Map::ChangeStageAndRoom()
{
    switch (stage)
    {
    case Stages::Tutorial:
        switch (room)
        {
        case Rooms::Room1:
            room = Rooms::Room2;
            break;
        case Rooms::Room2:
            room = Rooms::Room3;
            break;
        case Rooms::Room3:
            room = Rooms::Room4;
            break;
        case Rooms::Room4:
            room = Rooms::Room5;
            break;
        case Rooms::Room5:
            room = Rooms::Room6;
            break;
        case Rooms::Room6:
            room = Rooms::Store;
            break;
        case Rooms::Store:
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
            break;
        }
        break;
    case Stages::stage1:
        switch (room)
        {
        case Rooms::Room1:
            room = Rooms::Room2;
            break;
        case Rooms::Room2:
            room = Rooms::Room3;
            break;
        case Rooms::Room3:
            room = Rooms::Store;
            break;
        case Rooms::Store:
            room = Rooms::Room1;
            stage = Stages::stage2;            
            break;
        }
        break;
    case Stages::stage2:
        switch (room)
        {
        case Rooms::Room1:
            room = Rooms::Room2;
            break;
        case Rooms::Room2:
            room = Rooms::Room3;
            break;
        case Rooms::Room3:
            room = Rooms::Store;
            break;
        case Rooms::Store:
            room = Rooms::Room1;
            stage = Stages::stage3;
            break;
        }
        break;
    case Stages::stage3:
        switch (room)
        {
        case Rooms::Room1:
            room = Rooms::Room2;
            break;
        case Rooms::Room2:
            room = Rooms::Room3;
            break;
        case Rooms::Room3:
            room = Rooms::Store;
            break;
        case Rooms::Store:
            room = Rooms::Room1;
            stage = Stages::Boss;
            break;
        }
        break;
    case Stages::Boss:
        switch (room)
        {
        case Rooms::Room1:
            room = Rooms::Room2;
            break;
        case Rooms::Room2:
            room = Rooms::Room3;
            break;
        case Rooms::Room3:
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
            break;
        }
    default:
        break;
    }
}

void Map::initialize_store()
{
    ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
    item_manager->StoreItem({ 1,1 });
    item_manager->StoreItem({ 2,1 });
    item_manager->StoreItem({ 3,1 });
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Merchant({ 2,2 }));
}


Map::Map(Stages start_stage, Rooms start_room):
    stage(start_stage),
    room(start_room),
    GameObject(start_position, 0.0, scale_const),
    enemy_trajectory("Assets/EnemyTrajectory.spt",this)
{   
    AddGOComponent(new CS230::Sprite("Assets/Tile_Assets.spt", this, true));
    InitializeStage(stage);  
}

void Map::Update([[maybe_unused]] double dt) {
    
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Tab)) {
        enemy_trajectory_draw = !enemy_trajectory_draw;
        if (enemy_trajectory_draw) {
            Engine::GetLogger().LogDebug("enemy tra drawing");
        }
        
    }
}

void Map::Draw(Math::TransformationMatrix camera_matrix) {
	CS230::Sprite* sprite = GetGOComponent<CS230::Sprite>();
	if (sprite != nullptr) {
        Math::TransformationMatrix start_matrix = GetMatrix();
        for (int j = 0; j < height_amount; ++j) {
            for (int i = 0; i < width_amount; ++i) {
                Math::TransformationMatrix draw_matrix = Math::TranslationMatrix(Math::vec2{ tile_size.x * i * GetScale().x, tile_size.y * j * GetScale().y }) * start_matrix;
                sprite->Draw(camera_matrix * draw_matrix, tile_design[i][j].tile_number);
                if (enemy_trajectory_draw == true && tile_design[i][j].isEnemyReachable == true) {
                    
                    enemy_trajectory.Draw(camera_matrix * draw_matrix);
                }
            }
        }
	}
}