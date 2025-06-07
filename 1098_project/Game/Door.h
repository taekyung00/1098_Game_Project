#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Vec2.h"
class Door : public CS230::GameObject {
public:
	Door(Math::ivec2 start_index);
    void Draw(Math::TransformationMatrix camera_matrix) override;
    GameObjectTypes Type() override { return GameObjectTypes::Door; }
    std::string TypeName() override { return "Door"; }
};