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
extern const Stages GetFirstStage();
extern const const Stages GetLastStage();
extern Stages& operator++(Stages& orig);
extern Stages& operator++(Stages& orig, int);
extern Stages& operator--(Stages& orig);
extern Stages& operator--(Stages& orig, int);


#endif // !STAGES_H
