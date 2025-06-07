#include "Stages.h"
const Stages GetFirstStage() {
    return static_cast<Stages>(static_cast<int>(Stages::First) + 1);
}
const Stages GetLastStage() {
    return static_cast<Stages>(static_cast<int>(Stages::End) - 1);
}
Stages& operator++(Stages& orig) {
    if (orig != GetLastStage()) {
        orig = static_cast<Stages>(static_cast<int>(orig) + 1);
    }
    return orig;
}
Stages operator++(Stages& orig, int) {
    Stages temp = orig;
    ++orig;
    return temp;
}

Stages& operator--(Stages& orig) {
    if (orig != GetFirstStage()) {
        orig = static_cast<Stages>(static_cast<int>(orig) - 1);
    }
    return orig;
}

Stages operator--(Stages& orig, int) {
    Stages temp = orig;
    --orig;
    return temp;
}