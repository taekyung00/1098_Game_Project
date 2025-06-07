#include "SpawnEnemy.h"

void SpawnEnemy::SpawnEnemies(std::vector<Enemy*>& enemies)
{
	for (Enemy* enemy : enemies) {
		enemy->Destroy();
	}
	enemies.clear();
	CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
	Map* map_ptr = gameobjectmanager->GetGameObject<Map>();
	const std::vector<std::vector<int>>& sp = map_ptr->GetSpawnLayer();

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

		}
	}


	Engine::GetLogger().LogDebug(std::to_string(static_cast<int>(enemies.size())));
}
