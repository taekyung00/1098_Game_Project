#include "CollisionManager.h"

CollisionManager::CollisionManager(Map& map, Player& player, std::vector<Enemy*>& enemies, std::vector<Trap*>& traps):
	map(map), player(player), enemies(enemies), traps(traps) { }

void CollisionManager::CollisionCheck()
{
	for (Enemy* enemy : enemies) {
		if (CheckCollisionRecs(player.GetPlayerRect(), enemy->GetRect())) {
			player.SetIsAlive() = false;
		}
	}
	for (Trap* trap : traps) {
		if ((trap->GetIsAlive() == true) && (CheckCollisionRecs(player.GetPlayerRect(), trap->GetTrapRect()))) {
			player.SetMovingCount()--;
			trap->SetIsAlive() = false;
			trap->SetIsOutdated() = false;
		}
	}
	if (CheckCollisionRecs(player.GetPlayerRect(), map.GetDownStairsRect())) {
		if (static_cast<int>(map.GetCurrentStage()) < static_cast<int>(Stages::stage3)) {
			++(map.SetCurrentStage());
		}
		else {
			Engine::GetGameStateManager().ClearNextGameState();
		}
	}

}
