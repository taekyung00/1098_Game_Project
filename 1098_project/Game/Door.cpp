#include "Door.h"

Door::Door(Math::ivec2 start_index) : 
	GameObject(start_index, 0.0, scale_const)
{
	AddGOComponent(new CS230::Sprite("Assets/Door.spt", this));
}

void Door::Draw(Math::TransformationMatrix camera_matrix) {
	CS230::GameObject::Draw(camera_matrix);
}


