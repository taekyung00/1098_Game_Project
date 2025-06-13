#pragma once
#include "../Engine/Component.h"
#include "../Engine/Sprite.h"
#include "../Engine/GameObjectManager.h"
#include "TurnManager.h"
#include "Item.h"

class Player;

class UI : public CS230::Component {
public:
	UI();
	void Update(double dt) override;
	void Draw();
private:
	CS230::Texture* ui;
	CS230::Texture* turn_button;
	CS230::Texture* axe_texture;
	CS230::Texture* spear_texture;
	CS230::Texture* shield_texture;
	CS230::Texture* boots_texture;
	//CS230::Texture* life_texture;
	const Player* player_ptr;
	const Math::ivec2 start_position = { 472,620 };
	const Math::ivec2 player_button_position = { 4,3 };
	const Math::ivec2 enemy_button_position = { 538,3 };
	const Math::ivec2 button_frame_size = { 175,37 };
	std::vector<Math::vec2> draw_use_items_position = {
		{53.0,448.0},{154.0,448.0},{53.0,343.0},{154.0,343.0},{53.0,238.0},{154.0,238.0},{53.0,133.0},{154.0,133.0}
	};
	std::vector<Math::ivec2> use_items_texel_positions = {
		{0,0}, {32,0}, {64,0}, {96,0}
	};
	const Math::ivec2 use_items_frame_size = { 32,32 };
};