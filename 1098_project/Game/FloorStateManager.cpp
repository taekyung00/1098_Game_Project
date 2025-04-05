#include "FloorStateManager.h"

FloorStateManager::FloorStateManager() :
	current_floor(nullptr),
	next_floor(nullptr),
	status(Status::STARTING)
{
}

void FloorStateManager::Update(double dt){
    switch (status) {
    case Status::STARTING:
        //Your Code
        if (floorstates.size() != 0) {
            next_floor = floorstates[0];
            status = Status::LOADING;
        }
        else {
            status = Status::STOPPING;
        }

        break;
    case Status::LOADING:
        current_floor = next_floor;
        Engine::GetLogger().LogEvent("Load " + current_floor->GetName());
        current_floor->Load();
        Engine::GetLogger().LogEvent("Load Complete");
        status = Status::UPDATING;
        break;
    case Status::UPDATING:
        //Your Code
        if (current_floor != next_floor) {
            //do i have to call SetNextGameState() at here? --> "player" have to change gamestate by play ?!
            status = Status::UNLOADING;
        }
        else {
            Engine::GetLogger().LogVerbose("Update " + current_floor->GetName());
            current_floor->Update(dt);
            current_floor->Draw();
        }
        break;
    case Status::UNLOADING:
        //Your Code
        Engine::GetLogger().LogEvent("Unload " + current_floor->GetName());
        current_floor->Unload();
        Engine::GetLogger().LogEvent("Unload Complete");
        if (next_floor == nullptr) {
            status = Status::STOPPING;
        }
        else {
            status = Status::LOADING;
        }
        break;
    case Status::STOPPING:
        //Your Code
        status = Status::EXIT;
        break;
    case Status::EXIT:
        break;
    }
}

void FloorStateManager::AddFloor(FloorState& floorstate){
	floorstates.push_back(&floorstate);
}

void FloorStateManager::SetNextFloor(int index){
	next_floor = floorstates[index];
}

void FloorStateManager::ClearNextFloor(){
	next_floor = nullptr;
}

void FloorStateManager::ReloadFloor(){
	status = Status::UNLOADING;
}

bool FloorStateManager::HasFloorEnded(){
	return status == Status::EXIT;
}
