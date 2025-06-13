#include "UI.h"
#include "Player.h"

UI::UI():
	ui(Engine::GetTextureManager().Load("Assets/UI.png")),
	turn_button(Engine::GetTextureManager().Load("Assets/TurnButton.png")),
	axe_texture(Engine::GetTextureManager().Load("Assets/Axe.png")),
	spear_texture(Engine::GetTextureManager().Load("Assets/Spear.png")),
	shield_texture(Engine::GetTextureManager().Load("Assets/Shield.png")),
	boots_texture(Engine::GetTextureManager().Load("Assets/Boots.png")),
	player_ptr(Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>())
{}

void UI::Update([[maybe_unused]] double dt) {

}
void UI::Draw() {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	const std::vector<Item*>& player_use_items = player_ptr->GetUseItem();
	ui->Draw(Math::TranslationMatrix(Math::ivec2{0,0}));
	if (turnmanager->GetCurrentTurn() == Turns::Player) {
		turn_button->Draw(Math::TranslationMatrix(start_position), player_button_position, button_frame_size);
	}
	else if (turnmanager->GetCurrentTurn() == Turns::Enemy) {
		turn_button->Draw(Math::TranslationMatrix(start_position + Math::ivec2{ (enemy_button_position.x) / static_cast<int>(scale_const.x),0 }), enemy_button_position, button_frame_size);
	}
	if (player_use_items.size() != 0) {
		
		for (int i = 0; i < player_use_items.size(); ++i) {
			
			Math::TransformationMatrix item_draw_matrix = Math::TranslationMatrix(draw_use_items_position[i]) * Math::ScaleMatrix(scale_const);
			Math::TransformationMatrix life_draw_matrix = Math::TranslationMatrix(draw_use_items_position[i]) * Math::ScaleMatrix(scale_const/2);

			switch (player_use_items[i]->Type())
			{
			case GameObjectTypes::Axe:
				axe_texture->Draw(item_draw_matrix, use_items_texel_positions[static_cast<int>(player_use_items[i]->GetUseItemRank())], use_items_frame_size);
				break;
			case GameObjectTypes::Spear:
				spear_texture->Draw(item_draw_matrix, use_items_texel_positions[static_cast<int>(player_use_items[i]->GetUseItemRank())], use_items_frame_size);
				break;
			case GameObjectTypes::Shield:
				shield_texture->Draw(item_draw_matrix, use_items_texel_positions[static_cast<int>(player_use_items[i]->GetUseItemRank())], use_items_frame_size);
				break;
			case GameObjectTypes::Boots:
				boots_texture->Draw(item_draw_matrix, use_items_texel_positions[static_cast<int>(player_use_items[i]->GetUseItemRank())], use_items_frame_size);
				break;
			}
			player_use_items[i]->LifeTexture()->Draw(life_draw_matrix);
		}
	}
	//Engine::GetLogger().LogDebug("ui drawing");
	
}
