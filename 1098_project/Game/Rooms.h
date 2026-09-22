#pragma once
enum class Rooms {
    Room1,
    Room2,
    Room3,
    Room4,
    Room5,
    Room6,
    Room7,
    Store,
    Count // for check
};
Rooms& operator++(Rooms& orig);
//Rooms& operator--(Rooms& orig);