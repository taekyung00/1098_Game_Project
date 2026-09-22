#pragma once

enum class Turns
{
	Player,
	Enemy
};

Turns& operator++(Turns& orig);