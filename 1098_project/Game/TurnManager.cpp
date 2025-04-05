#include "TurnManager.h"



TurnManager::TurnManager() : 
	player_turn_count(max_turn_count),
	enemy_turn_count(max_turn_count){}

void TurnManager::Load(){
	isplayerturn = true;
	isenemyturn = false;
	player_turn_count = max_turn_count;
	enemy_turn_count = max_turn_count;
}

void TurnManager::Update(double dt)
{
	if (isplayerturn) {
		player_turn_count -= dt;
	}
	if (isenemyturn) {
		enemy_turn_count -= dt;
	}
	if (player_turn_count <= 0) {
		PlayerToEnemy();
	}
	if (enemy_turn_count <= 0) {
		EnemyToPlayer();
	}
}

void TurnManager::PlayerToEnemy(){
	isplayerturn = false;
	isenemyturn = true;
	player_turn_count = max_turn_count;
	enemy_turn_count = max_turn_count;	
}

void TurnManager::EnemyToPlayer(){
	isplayerturn = true;
	isenemyturn = false;
	player_turn_count = max_turn_count;
	enemy_turn_count = max_turn_count;
}


