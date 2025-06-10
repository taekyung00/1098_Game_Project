#include "Axe.h"
#include "Player.h"

Axe::Axe(Math::ivec2 start_index, ItemKind item_kind, UseItem use_item, UseItemRank use_item_rank) :
	Item(start_index, item_kind, use_item, use_item_rank),
	cost_texture(nullptr)
{
	AddGOComponent(new CS230::Sprite("Assets/Axe.spt", this));
	is_get = false;
	switch (use_item_rank)
	{
	case UseItemRank::Common:
		life = 1;
		cost = 3;
		break;
	case UseItemRank::Rare:
		life = 2;
		cost = 4;
		break;
	case UseItemRank::Unique:
		life = 3;
		cost = 5;
		break;
	case UseItemRank::Legendary:
		life = 5;
		cost = 6;
		break;
	}
	
}

void Axe::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	
	if (other_object->Type() == GameObjectTypes::Player) {
		SetIndex() = {-10,-10};
		SetPosition({-100,-100});
		item_manager->PushUseItemToPlayer(this);
		turn_manager->Sub(cost);
		is_get = true;
	}
}

void Axe::Update([[maybe_unused]]double dt) {
	ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if (life <= 0) {
		item_manager->EraseUseItem(this);
		player->EraseUseItem(this);
	}
}

void Axe::Draw(Math::TransformationMatrix camera_matrix) {
	if (is_get == false) {
		Math::TransformationMatrix draw_matrix = GetMatrix();
		CS230::Sprite* sprite = GetGOComponent<CS230::Sprite>();
		if (sprite != nullptr) {
			sprite->Draw(draw_matrix, static_cast<int>(use_item_rank));
		}		
		cost_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture(std::to_string(cost), 0xFFFFFFF7);
		cost_texture->Draw(draw_matrix );
	}
}