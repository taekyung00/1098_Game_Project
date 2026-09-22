
#pragma once
#include "../Engine/GameObject.h"
class Merchant : public CS230::GameObject {
public:
	Merchant(Math::ivec2 index);
	GameObjectTypes Type() override { return GameObjectTypes::Merchant; }
	std::string		TypeName() override { return "Merchant"; }
	void Update(double dt) override;
	void Draw(Math::TransformationMatrix camera_matrix) override;
private:
	CS230::Sprite merchant_carpet;
};