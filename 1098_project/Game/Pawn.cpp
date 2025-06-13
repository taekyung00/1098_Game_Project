#include "Pawn.h"
#include "Rook.h"
#include "TurnManager.h"
#include "Player.h"

Pawn::Pawn(Math::ivec2 index) :
	Enemy(index) 
	//movable("Assets/Movable.spt", this)
{
	AddGOComponent(new CS230::Sprite("Assets/Pawn.spt", this));
	ReachableIndexPush();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
	//ChangeMapDesign();
	turn_timer = new CS230::Timer(0.0);
	AddGOComponent(turn_timer);
}


void Pawn::Update(double dt) {
	if (Destroyed() == true) {
		return;
	}
	GameObject::Update(dt);
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacked)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Defeated));
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Defeated))) {
		if ((GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
			Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->EraseEnemy(this);
			Destroy();
			Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(GetIndex());
		}
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacking)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
	}
	if ((turn_ended == false) && (is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		ReachableIndexPush();
		ChangeIndex();
		ReachableIndexPush();

		SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
		is_outdated = false;
		Engine::GetLogger().LogDebug("Enemy is updated");
		turn_timer->Set(turn_time);
	}
	if ((turn_ended == false) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		if (turn_timer->Remaining() == 0.0) {
			turn_ended = true;
			is_outdated = true;
		}
	}
	ChangeMapDesign();
}

void Pawn::ReachableIndexPush()
{
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	reachable_indices.clear();

	Math::ivec2 temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isLeftEdge == false) {
		temp_index.x--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isRightEdge == false) {
		temp_index.x++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isBottomEdge == false) {
		temp_index.y--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isTopEdge == false) {
		temp_index.y++;
		reachable_indices.push_back(temp_index);
	}
}

void Pawn::Draw(Math::TransformationMatrix camera_matrix) {
	GameObject::Draw(camera_matrix);
	//movable.Draw(camera_matrix * GetMatrix());
}

void Pawn::attack() {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
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
			turnmanager->Sub(1);
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			did_attack = true;
			player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
		}		
		
	}
}

void Pawn::Defeated()
{
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacked));
}