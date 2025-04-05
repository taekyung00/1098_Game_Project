#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#pragma once

class TurnManager {
public:
	TurnManager();
	void Update(double);
	bool GetIsTurnEnd() { return isturnend; }
private:
	const double max_turn_count = 3;
	bool isturnend;	
	double turn_count;
	
};
#endif // !TURNMANAGER_H


