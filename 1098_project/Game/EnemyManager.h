#pragma once
#include <vector>
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Component.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Map.h"
#include "Cannon.h"
#include "Trap.h"
#include "Archer.h"
#include "InGame.h"
#include "King.h"

class EnemyManager : public CS230::Component {
public:
	void SpawnEnemies();
	//void SpawnEnemiesTutorial();
	void TurnChange();
	//void ClearEnemies();
	std::vector<Enemy*>& SetEnemies() { return enemies; }
	const std::vector<Enemy*>& GetEnemies() const { return enemies; }

	void EraseEnemy(Enemy* enemy);


private:
	std::vector<Enemy*> enemies;
	std::vector<std::vector<int>> spawn_layer;
	std::vector<std::vector<int>> spawn_trap_layer;
};
