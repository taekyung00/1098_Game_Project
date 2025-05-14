#ifndef ROOK_H
#define ROOK_H

#include"../Engine/Vec2.h"

#include "Enemy.h"
class Rook : public Enemy {
public:
	Rook(Math::ivec2 index, std::string sprite_path);
	void Load() override;
	void Update(double dt) override;
	void ReachableTest() override;
	void ChangeMapDesign() override;
	~Rook();
};
#endif // !ROOK_H

