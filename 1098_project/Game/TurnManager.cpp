#include "TurnManager.h"
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
	turn_count += dv;
}