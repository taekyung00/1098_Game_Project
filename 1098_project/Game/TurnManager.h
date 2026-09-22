#pragma once
#include "../Engine/Component.h"
#include "Turns.h"


class TurnManager : public CS230::Component {
public:
	TurnManager(int start_turn_count,Turns start_turn);
	//void Update(double dt) override;
	void Sub(int dv = 1);
	void Add(int dv = 1);
	const int GetTurnCount() const { return turn_count; }
	const Turns GetCurrentTurn() const { return current_turn; }
	Turns& SetCurrentTurn()  { return current_turn; }
private:
	int turn_count;
	Turns current_turn;
};
