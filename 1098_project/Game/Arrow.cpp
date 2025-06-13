#include "Arrow.h"
#include "Player.h"

Arrow::Arrow(Math::ivec2 start_index, Math::ivec2 dest_index) :
	 Enemy(dest_index),
	dest_index(dest_index),
	start_index(start_index)
{
	AddGOComponent(new CS230::Sprite("Assets/Arrow.spt", this));
	
	//dest_pos = { start_position.x + dest_index.x * tile_size.x * scale_const.x , start_position.y + dest_index.y * tile_size.y * scale_const.y };
	//temp_pos = GetPosition();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
	
}

void Arrow::Update([[maybe_unused]] double dt) {
	GameObject::Update(dt);
	
	if (dest_index != start_index)
	{
		if (dest_index.x- start_index.x > 0) {
			++start_index.x;
		}
		else if (dest_index.x - start_index.x < 0) {
			--start_index.x;
		}

		if (dest_index.y - start_index.y > 0) {
			++start_index.y;
		}
		else if (dest_index.y - start_index.y < 0) {
			--start_index.y;
		}
		
	}
	else {
		//ResolveCollision(Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>());
		turn_ended = true;
		//Destroyed();
		
	}
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if (turnmanager->GetCurrentTurn() == Turns::Player) {
		Destroy();
	}
	SetPosition({ start_position.x + start_index.x * tile_size.x * scale_const.x, start_position.y + start_index.y * tile_size.y * scale_const.y });
}
void Arrow::ResolveCollision(GameObject* other_object) {
	if (Destroyed() == true) {
		return;
	}
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		std::vector<Item*>& player_use_items = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>()->SetUseItem();
		std::vector<Item*>::iterator item_iter = std::find_if(player_use_items.begin(), player_use_items.end(), [](Item* item) {
			return item->Type() == GameObjectTypes::Shield;
			});
		if (item_iter != player_use_items.end()) {
			Shield* shield = static_cast<Shield*>(*(item_iter));
			--shield->SetLife();
			if (shield->GetLife() == 0) {
				ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
				//Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
				item_manager->EraseUseItem(shield);
				player->EraseUseItem(shield);
			}
		}
		else {
			turnmanager->Sub(2);
			did_attack = true;
			player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
			Destroy();
		}		
		
	}
}
