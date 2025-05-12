#include "CollisionManager.h"

CollisionManager::CollisionManager(Player& player, std::vector<Enemy*>& enemies):
	player(player),enemies(enemies){}

void CollisionManager::CollisionCheck()
{
	for (Enemy* enemy : enemies) {
		if (CheckCollisionRecs(player.GetPlayerRect(), enemy->GetRect())) {
			player.SetIsAlive() = false;
		}
	}
}
