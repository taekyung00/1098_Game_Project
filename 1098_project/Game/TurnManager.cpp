#include "TurnManager.h"

TurnManager::TurnManager() : isturnend(false),turn_count(max_turn_count){}

void TurnManager::Update(double dt){
	turn_count -= dt;
}
