#include "CannonBall.h"
#include "Player.h"

CannonBall::CannonBall(Math::ivec2 index) :
	Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/CannonBall.spt", this));
}
void CannonBall::Update([[maybe_unused]]double dt) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if (turnmanager->GetCurrentTurn() == Turns::Player) {
		Destroy();
	}
}
void CannonBall::ResolveCollision(GameObject* other_object) {
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
			turnmanager->Sub(3);
			did_attack = true;
			player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
			Destroy();
		}
		
		
	}
}

