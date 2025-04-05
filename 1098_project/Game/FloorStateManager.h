#ifndef FLOORSTATEMANAGER_H
#define FLOORSTATEMANAGER_H
#pragma once

#include "FloorState.h"
#include "../Engine/Engine.h"

#include <vector>

class FloorStateManager {
public:
    FloorStateManager();

    void Update(double);
    void AddFloor(FloorState& floorstate);
    void SetNextFloor(int index);
    void ClearNextFloor();
    void ReloadFloor();
    bool HasFloorEnded();

private:
    enum class Status {
        STARTING,
        LOADING,
        UPDATING,
        UNLOADING,
        STOPPING,
        EXIT
    };

    Status status;
    std::vector<FloorState*> floorstates;
    FloorState* current_floor;
    FloorState* next_floor;
};
#endif // !FLOORSTATEMANAGER_H


