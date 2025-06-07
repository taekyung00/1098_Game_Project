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
#include "Cannon.h"
#include "Trap.h"
#include "Archer.h"
#include "InGame.h"

class SpawnEnemy : public CS230::Component
{
public:
	void SpawnEnemies();
	

private:

};



