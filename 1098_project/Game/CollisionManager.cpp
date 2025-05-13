#include "CollisionManager.h"

CollisionManager::CollisionManager(Player& player, std::vector<Enemy*>& enemies, std::vector<Trap*>& traps):
	player(player),enemies(enemies), traps(traps){}

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

}
