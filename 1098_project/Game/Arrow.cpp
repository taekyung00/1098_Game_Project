#include "Arrow.h"

Arrow::Arrow(Math::ivec2 index) :
	 Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/Arrow.spt", this));
}
