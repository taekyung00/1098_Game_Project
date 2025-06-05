#ifndef STAGES_H
#define STAGES_H
#pragma once
enum class Stages {
    First, // for check
    stage1,
    stage2,
    stage3,
    End // for check
};
const Stages GetFirstStage();
const Stages GetLastStage();
Stages& operator++(Stages& orig);
Stages operator++(Stages& orig, int);
Stages& operator--(Stages& orig);
Stages operator--(Stages& orig, int);


#endif // !STAGES_H
