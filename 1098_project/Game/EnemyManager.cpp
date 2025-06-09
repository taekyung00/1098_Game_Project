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
	[[maybe_unused]] const std::vector<std::vector<int>>& sp = map_ptr->GetSpawnLayer();


	for (int i = 0; i < sp.size(); ++i) {
		for (int j = 0; j < sp[i].size(); ++j) {
			int id = sp[i][j];
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

	const std::vector<std::vector<int>>& spt = map_ptr->GetSpawnTrapLayer();
	for (int i = 0; i < spt.size(); ++i) {
		for (int j = 0; j < spt[i].size(); ++j) {
			int id = spt[i][j];
			if (id == 1) {
				Enemy* enemy = new Trap({ i,j });
				enemies.push_back(enemy);
				gameobjectmanager->Add(enemy);
			}
		}
	}

	Engine::GetLogger().LogDebug(std::to_string(static_cast<int>(enemies.size())));
}

void EnemyManager::SpawnEnemiesTutorial()
{
	for (Enemy* enemy : enemies) {
		enemy->Destroy();
	}
	enemies.clear();
	CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
	Map* map_ptr = gameobjectmanager->GetGameObject<Map>();
	[[maybe_unused]] const std::vector<std::vector<int>>& sp = map_ptr->GetSpawnLayer();
	if (map_ptr->GetStage() == Stages::Tutorial) {
		switch (map_ptr->GetRoom())
		{

		default:
			break;
		}
	}
	else {
		Engine::GetLogger().LogDebug("Use Wrong SpawnEnemies!!");
	}
}

void EnemyManager::TurnChange()
{
	bool are_enemies_all_outdated = true;
	for (Enemy* enemy : enemies) {
		if (enemy->GetIsOutdated() == false) {
			are_enemies_all_outdated = false;
			break;
		}
	}

	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Turns current_turn = turn_manager->GetCurrentTurn();
	if ((current_turn == Turns::Enemy) && (are_enemies_all_outdated == true)) {
		for (Enemy* enemy : enemies) {
			enemy->SetDidAttact() = false;
		}
		turn_manager->SetCurrentTurn() = Turns::Player;
	}

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

//void EnemyManager::ClearEnemies()
//{
//	enemies.clear();
//}
