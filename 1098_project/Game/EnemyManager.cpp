#include "EnemyManager.h"
#include "Enemy.h"
void EnemyManager::SpawnEnemies()
{
	for (Enemy* enemy : enemies) {
		enemy->Destroy();
	}
	enemies.clear();
	CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
	Map* map_ptr = gameobjectmanager->GetGameObject<Map>();
	//[[maybe_unused]] const std::vector<std::vector<int>>& sp = map_ptr->GetSpawnLayer();
	const std::string& designPath = map_ptr->GetDesignPath();

	//enemy path init
	std::filesystem::path mapPath{ designPath };
	auto spawnFs = mapPath.parent_path()
		/ (mapPath.stem().string() + "_m.txt");
	std::string spawnPath = spawnFs.string();
	Engine::GetLogger().LogDebug(spawnPath.c_str());

	//trap path init

	auto spawnTFs = mapPath.parent_path()
		/ (mapPath.stem().string() + "_t.txt");
	std::string spawnTrapPath = spawnTFs.string();
	Engine::GetLogger().LogDebug(spawnTrapPath.c_str());
	/*=========================================================*/

	spawn_layer.clear();
	spawn_trap_layer.clear();

	std::string temp_string;

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

	//spawn_layer flip! - to use [0,0] as bottom-left

	for (int i = 0; i < (spawn_layer.size() - 1) / 2; ++i) {
		for (int j = 0; j < spawn_layer[i].size(); ++j) {
			int temp = spawn_layer[i][j];
			spawn_layer[i][j] = spawn_layer[spawn_layer.size() - 1 - i][j];
			spawn_layer[spawn_layer.size() - 1 - i][j] = temp;
		}
	}

	for (int i = 0; i < spawn_layer.size(); ++i) {
		for (int j = i; j < spawn_layer[i].size(); ++j) {
			int temp = spawn_layer[i][j];
			spawn_layer[i][j] = spawn_layer[j][i];
			spawn_layer[j][i] = temp;
		}

	}
	spawnStream.close();



	std::ifstream spawnTrapStream(spawnTrapPath);
	if (!spawnTrapStream.is_open())
		throw std::runtime_error("fail to open spawn Trap file: " + spawnTrapPath);

	while (std::getline(spawnTrapStream, temp_string)) {
		std::stringstream ss(temp_string);
		std::vector<int> row;
		std::string cell;
		while (std::getline(ss, cell, ',')) {
			cell.erase(0, cell.find_first_not_of(" \t"));
			cell.erase(cell.find_last_not_of(" \t") + 1);
			row.push_back(cell.empty() ? 0 : std::stoi(cell));
		}
		spawn_trap_layer.push_back(std::move(row));
	}

	//spawn_layer flip! - to use [0,0] as bottom-left

	for (int i = 0; i < (spawn_trap_layer.size() - 1) / 2; ++i) {
		for (int j = 0; j < spawn_trap_layer[i].size(); ++j) {
			int temp = spawn_trap_layer[i][j];
			spawn_trap_layer[i][j] = spawn_trap_layer[spawn_trap_layer.size() - 1 - i][j];
			spawn_trap_layer[spawn_trap_layer.size() - 1 - i][j] = temp;
		}
	}

	for (int i = 0; i < spawn_trap_layer.size(); ++i) {
		for (int j = i; j < spawn_trap_layer[i].size(); ++j) {
			int temp = spawn_trap_layer[i][j];
			spawn_trap_layer[i][j] = spawn_trap_layer[j][i];
			spawn_trap_layer[j][i] = temp;
		}

	}
	spawnTrapStream.close();

	for (int i = 0; i < spawn_layer.size(); ++i) {
		for (int j = 0; j < spawn_layer[i].size(); ++j) {
			int id = spawn_layer[i][j];
			if (id == 1) {
				Enemy* enemy = new Pawn({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
			if (id == 2) {
				Enemy* enemy = new Rook({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
			if (id == 3) {
				Enemy* enemy = new Bishop({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
			if (id == 4) {
				Enemy* enemy = new Cannon({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
			if (id == 5) {
				Enemy* enemy = new Archer({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
		}
	}

	//const std::vector<std::vector<int>>& spt = map_ptr->GetSpawnTrapLayer();
	for (int i = 0; i < spawn_trap_layer.size(); ++i) {
		for (int j = 0; j < spawn_trap_layer[i].size(); ++j) {
			int id = spawn_trap_layer[i][j];
			if (id == 1) {
				Enemy* enemy = new Trap({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
		}
	}

	Engine::GetLogger().LogDebug(std::to_string(static_cast<int>(enemies.size())));
}

//void EnemyManager::SpawnEnemiesTutorial()
//{
//	for (Enemy* enemy : enemies) {
//		enemy->Destroy();
//	}
//	enemies.clear();
//	CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
//	Map* map_ptr = gameobjectmanager->GetGameObject<Map>();
//	[[maybe_unused]] const std::vector<std::vector<int>>& sp = map_ptr->GetSpawnLayer();
//	if (map_ptr->GetStage() == Stages::Tutorial) {
//		switch (map_ptr->GetRoom())
//		{
//
//		default:
//			break;
//		}
//	}
//	else {
//		Engine::GetLogger().LogDebug("Use Wrong SpawnEnemies!!");
//	}
//}

void EnemyManager::TurnChange()
{
	bool are_enemies_turn_ended = true;
	for (Enemy* enemy : enemies) {
		if (enemy->GetTurnEnded() == false) {
			are_enemies_turn_ended = false;
			break;
		}
	}

	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Turns current_turn = turn_manager->GetCurrentTurn();
	if ((current_turn == Turns::Enemy) && (are_enemies_turn_ended == true)) {
		for (Enemy* enemy : enemies) {
			enemy->SetDidAttact() = false;
			enemy->SetTurnEnded() = false;
		}
		turn_manager->SetCurrentTurn() = Turns::Player;
	}

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

void EnemyManager::EraseEnemy(Enemy* enemy)
{
	enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

//void EnemyManager::ClearEnemies()
//{
//	enemies.clear();
//}
