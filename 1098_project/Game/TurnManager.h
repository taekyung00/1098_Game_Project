#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#pragma once

class TurnManager {
public:

	void Update();
private:
	bool isplayerturn = true;
	bool isenemyturn = false;
	
};
#endif // !TURNMANAGER_H


