#include "Rook.h"
#include "Player.h"

Rook::Rook(Math::ivec2 index) :
	Enemy(index)
	//movable("Assets/Movable.spt",this)
{
	AddGOComponent(new CS230::Sprite("Assets/Rook.spt", this));
	ReachableIndexPush();
	ChangeMapDesign();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	turn_timer = new CS230::Timer(0.0);
	AddGOComponent(turn_timer);
}

void Rook::Update([[maybe_unused]] double dt) {
	if (Destroyed() == true) {
		return;
	}
	GameObject::Update(dt);
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacked)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Defeated));
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Defeated)) ) {
		if ((GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
			Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->EraseEnemy(this);
			Destroy();
			Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(GetIndex());
		}		
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacking)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded() == true)) {
		if (current_turn == 0) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
		}
		else {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
		}
	}
	if ((turn_ended == false) && (is_outdated == true) && (turn_manager->GetCurrentTurn() == Turns::Enemy)) {
		ReachableIndexPush();
		
		if (current_turn == 0) {
			current_turn = max_turn_count;
			
			ChangeIndex();
		}
		else {
			
			--current_turn;
		}
		if (current_turn == 0) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
		}
		else {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
		}
		
		ReachableIndexPush();
		
		//ChangeMapDesign();
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

void Rook::ReachableIndexPush() {
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	reachable_indices.clear();

	Math::ivec2 temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isLeftEdge == false)
	{
		temp_index.x--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isRightEdge == false)
	{
		temp_index.x++;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isBottomEdge == false)
	{
		temp_index.y--;
		reachable_indices.push_back(temp_index);
	}

	temp_index = GetIndex();
	while (map->GetTileDesign()[temp_index.x][temp_index.y].isTopEdge == false)
	{
		temp_index.y++;
		reachable_indices.push_back(temp_index);
	}
}

void Rook::Draw(Math::TransformationMatrix camera_matrix) {
	
	//if (current_turn == 0) {
	//	//GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attackable));
	//	movable.Draw(camera_matrix * GetMatrix());
	//}
	GameObject::Draw(camera_matrix);
}

void Rook::attack() {
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
			turnmanager->Sub(3);
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			did_attack = true;
			player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
		}
		
		
	}
}

void Rook::Defeated()
{
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacked));
}
