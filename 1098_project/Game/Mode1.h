#ifndef MODE1_H
#define MODE1_H
#pragma once

#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Camera.h"
#include "../Engine/GameState.h"

#include "FloorStateManager.h"
#include "Floor1.h"
#include "Floor2.h"

#include <vector>


class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update(double) override;
    void Unload() override;
    void Draw() override;

    FloorStateManager GetFloorStateManager() { return floorstatemanager; }
    std::string GetName() override {
        return "Mode1";
    }
    

private:
    FloorStateManager floorstatemanager;
    Floor1 floor1;
    Floor2 floor2;
};
#endif // !MODE_H


