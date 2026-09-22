#include "Turns.h"

Turns& operator++(Turns& orig)
{
	if (orig == Turns::Player) {
		orig = Turns::Enemy;
	}
	else if (orig == Turns::Enemy) {
		orig = Turns::Player;
	}
	return orig;
}
