#include "TurnManager.h"
#include "InGame.h"
TurnManager::TurnManager(int start_turn_count, Turns start_turn) : turn_count(start_turn_count), current_turn(start_turn)
{
}

void TurnManager::Sub(int dv)
{
	if (turn_count > 0) {
		turn_count -= dv;
	}
}

void TurnManager::Add(int dv)
{
	if (turn_count + dv > InGame::MaxTurn) {
		turn_count = InGame::MaxTurn;
	}
	else {
		turn_count += dv;
	}	
}