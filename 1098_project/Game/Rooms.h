#pragma once
enum class Rooms {
    Room1,
    Room2,
    Room3,
    Store,
    Count // for check
};
Rooms& operator++(Rooms& orig);
//Rooms& operator--(Rooms& orig);