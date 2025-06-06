#include "CannonBall.h"

CannonBall::CannonBall(Math::ivec2 index) :
	Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/CannonBall.spt", this));
}

