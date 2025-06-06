#include "Rooms.h"

Rooms& operator++(Rooms& orig)
{
	orig = (orig == Rooms::Room3 ? Rooms::Room1 : static_cast<Rooms>((static_cast<int>(orig) + 1)));
	return orig;
}

