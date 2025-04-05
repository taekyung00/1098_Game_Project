#pragma once
#include <string>

class FloorState {
public:
    virtual void Load() = 0;
    virtual void Update(double) = 0;
    virtual void Unload() = 0;
    virtual std::string GetName() = 0;
    virtual void Draw() = 0;

private:
};
