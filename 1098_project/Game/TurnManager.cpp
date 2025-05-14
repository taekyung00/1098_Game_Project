#include "TurnManager.h"



TurnManager::TurnManager() :
	current_turn(Turns::player),
	//player_turn_count(max_player_turn_count),
	enemy_turn_count(max_enemy_turn_count) {
}

void TurnManager::Load() {
	/*isplayerturn = true;
	isenemyturn = false;*/
	//player_turn_count = max_player_turn_count;
	enemy_turn_count = max_enemy_turn_count;
	trap_turn_count = max_trap_turn_count;
}

void TurnManager::Update(double dt)
{
	switch (current_turn)
	{
	/*case TurnManager::Turns::player:
		player_turn_count -= dt;
		break;*/
	case TurnManager::Turns::enemy:
		enemy_turn_count -= dt;
		break;
	case TurnManager::Turns::traps:
		trap_turn_count -= dt;
		break;
	}
	/*if (isplayerturn) {
		player_turn_count -= dt;
	}
	if (isenemyturn) {
		enemy_turn_count -= dt;
	}*/
	//if (player_turn_count <= 0) {
	//	current_turn = Turns::enemy;
	//	//PlayerToEnemy();
	//	CountReset();
	//}
	if (enemy_turn_count <= 0) {
		current_turn = Turns::traps;
		CountReset();
		//EnemyToPlayer();
	}

	if (trap_turn_count <= 0) {
		current_turn = Turns::player;
		CountReset();
	}
}

//void TurnManager::PlayerToEnemy() {
//	isplayerturn = false;
//	isenemyturn = true;
//	player_turn_count = max_player_turn_count;
//	enemy_turn_count = max_enemy_turn_count;
//}
//
//void TurnManager::EnemyToPlayer() {
//	isplayerturn = true;
//	isenemyturn = false;
//	
//}

void TurnManager::CountReset()
{
	//player_turn_count = max_player_turn_count;
	enemy_turn_count = max_enemy_turn_count;
	trap_turn_count = max_trap_turn_count;
}


