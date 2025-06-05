#pragma once
#include <vector>
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Component.h"
#include "Enemy.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Map.h"

class SpawnEnemy : public CS230::Component
{
public:
	void SpawnEnemies(std::vector<Enemy*>& enemies);
	

private:

};


