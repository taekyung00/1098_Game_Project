#include "Player.h"

#include "Enemy.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "EnemyManager.h"
#include "Axe.h"
#include "Spear.h"

Player::Player() :
	GameObject(Math::ivec2{2,0}, 0.0, scale_const),
	turn_manager(Engine::GetGameStateManager().GetGSComponent<TurnManager>())
{
	AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
	moving_sound_ptr = new Audio("Sounds/Moving_Sound.mp3");
	moving_sound_ptr->SetLooping(false);
	AddGOComponent(moving_sound_ptr);
	map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	//after_move_timer = new CS230::Timer(0.0);
	//AddGOComponent(after_move_timer);
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void Player::Update([[maybe_unused]]double dt) {
	GameObject::Update(dt);
	moving_sound_ptr->Update();
	const std::vector<Enemy*>& enemies = Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->GetEnemies();

	if (turn_manager->GetTurnCount() <= 0 && (GetGOComponent<CS230::Sprite>()->CurrentAnimation() != static_cast<int>(Animations::Defeated))) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Defeated));
		return;
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Defeated)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded())) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
	if ((GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attacked)) && (GetGOComponent<CS230::Sprite>()->AnimationEnded())) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	}

	if ((turn_manager->GetCurrentTurn() == Turns::Player)) {
		
		
		if ((turn_manager->GetTurnCount() > 0) && (is_moving == true) ) {
			if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
				if (use_items.size() != 0 && used_item == false) {
					attack(CS230::Input::Keys::A);
				}
				if (used_item == false) {
					move_left();
				}
			}
			else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
				if (use_items.size() != 0 && used_item == false) {
					attack(CS230::Input::Keys::S);
				}
				if (used_item == false) {
					move_bottom();
				}
				
			}
			else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
				if (use_items.size() != 0 && used_item == false) {
					attack(CS230::Input::Keys::D);
				}
				if (used_item == false) {
					move_right();
				}
				
			}
			else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
				if (use_items.size() != 0 && used_item == false) {
					attack(CS230::Input::Keys::W);
				}
				if (used_item == false) {
					move_top();
				}
				
			}

		}
		if ((is_moving == false) && (turn_manager->GetTurnCount() > 0)   /*&&(after_move_timer->Remaining()==0.0)*/) {
			if (did_nothing == false &&
				(GetGOComponent<CS230::Sprite>()->CurrentAnimation() != static_cast<int>(Animations::Idle)) &&
				GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
				GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
				is_moving = true;
				if (enemies.size() != 0)  {
					(turn_manager->SetCurrentTurn()) = Turns::Enemy;
					used_item = false;
				}
			}
			else if (did_nothing == true) {
				is_moving = true;
				did_nothing = false;
				if (enemies.size() != 0) {
					(turn_manager->SetCurrentTurn()) = Turns::Enemy;
					used_item = false;
				}
			}
		}
		SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
	}
	
}

bool Player::CanCollideWith(GameObjectTypes other_object_type) {

	if (Engine::GetGameStateManager().GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Player) {
		if (other_object_type == GameObjectTypes::Door) {
			return true;
		}
	}
	
	return false;
}

void Player::ResolveCollision(GameObject* other_object) {
	switch (other_object->Type())
	{
	case GameObjectTypes::Door:
		Engine::GetWindow().Clear(0x000000FF);
		map->ChangeStageAndRoom();
		if (!(map->GetStage() == Stages::End && map->GetRoom() == Rooms::Count)) {
			turn_manager->SetCurrentTurn() = Turns::Player;

			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
			SetIndex() = start_index;
			map->InitializeStage(map->GetStage());
			
			
			Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->SpawnEnemies();
			Engine::GetGameStateManager().GetGSComponent<ItemManager>()->ClearDropItem();
			if (map->GetRoom() != Rooms::Store) {
				Engine::GetGameStateManager().GetGSComponent<ItemManager>()->ClearUseItem();
			}
			
			if (map->GetStage() != Stages::Tutorial) {
				InGame::ChangeAudio();
			}
			
			is_moving = true;
			
		}
		else {
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
		}
		
		break;
	//case GameObjectTypes::Enemy:
	//	turn_manager->Add(5);
	//	other_object->Destroy();
	//	Engine::GetLogger().LogDebug("enemy is destroyed!");
	//	std::vector<Enemy*>& enemies = InGame::SetEnemies();
	//	enemies.erase(std::remove(enemies.begin(), enemies.end(), other_object), enemies.end());
	//	break;
	}
}

void Player::ChangeAnimation(int new_anime)
{
	if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() != new_anime) {
		GetGOComponent<CS230::Sprite>()->PlayAnimation(new_anime);
	}
	
}

void Player::move_left()
{
	EnemyManager* enemy_manager = Engine::GetGameStateManager().GetGSComponent<EnemyManager>();
	std::vector<Enemy*>& enemies = enemy_manager->SetEnemies();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isLeftEdge == false) {
		bool enemy_attacked = false;
		for (Enemy* enemy : enemies) {
			if ((enemy->Type() == GameObjectTypes::Enemy) && (Math::ivec2{ GetIndex().x - 1, GetIndex().y } == enemy->GetIndex())) {
				enemy_attacked = true;
				
				enemy->Defeated();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				//enemy_manager->EraseEnemy(enemy);
				turn_manager->Add(2);
				GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			}
		}
		if (enemy_attacked == false) {
			--SetIndex().x;
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
		}
	}
	else {
		did_nothing = true;
	}
	if (map->GetRoom() != Rooms::Store) {
		turn_manager->Sub();
	}
	
	is_moving = false;
	moving_sound_ptr->Play();
}

void Player::move_right()
{
	std::vector<Enemy*>& enemies = Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->SetEnemies();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isRightEdge == false) {
		bool enemy_attacked = false;
		for (Enemy* enemy : enemies) {
			if ((enemy->Type() == GameObjectTypes::Enemy) && (Math::ivec2{ GetIndex().x + 1, GetIndex().y } == enemy->GetIndex())) {
				enemy_attacked = true;

				enemy->Defeated();
				//enemy->Destroy();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				//enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
				turn_manager->Add(2);
				GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			}
		}
		if (enemy_attacked == false) {
			++SetIndex().x;
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
		}
	}
	else {
		did_nothing = true;
	}
	if (map->GetRoom() != Rooms::Store) {
		turn_manager->Sub();
	}
	is_moving = false;
	moving_sound_ptr->Play();
}

void Player::move_top()
{
	std::vector<Enemy*>& enemies = Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->SetEnemies();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isTopEdge == false) {
		bool enemy_attacked = false;
		for (Enemy* enemy : enemies) {
			if ((enemy->Type() == GameObjectTypes::Enemy) && (Math::ivec2{ GetIndex().x , GetIndex().y + 1 } == enemy->GetIndex())) {
				enemy_attacked = true;

				enemy->Defeated();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				//enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
				turn_manager->Add(2);
				GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			}
		}
		if (enemy_attacked == false) {
			++SetIndex().y;
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
		}
	}
	else {
		did_nothing = true;
	}
	if (map->GetRoom() != Rooms::Store) {
		turn_manager->Sub();
	}
	is_moving = false;
	moving_sound_ptr->Play();
}

void Player::move_bottom()
{
	std::vector<Enemy*>& enemies = Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->SetEnemies();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isBottomEdge == false) {
		bool enemy_attacked = false;
		for (Enemy* enemy : enemies) {
			if ((enemy->Type() == GameObjectTypes::Enemy) && (Math::ivec2{ GetIndex().x , GetIndex().y - 1 } == enemy->GetIndex())) {
				enemy_attacked = true;

				enemy->Defeated();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				//enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
				turn_manager->Add(2);
				GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			}
		}
		if (enemy_attacked == false) {
			--SetIndex().y;
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
		}
	}
	else {
		did_nothing = true;
	}
	if (map->GetRoom() != Rooms::Store) {
		turn_manager->Sub();
	}
	is_moving = false;
	moving_sound_ptr->Play();
}

void Player::attack(CS230::Input::Keys input) {
	//ItemManager* item_manager = Engine::GetGameStateManager().GetGSComponent<ItemManager>();
	EnemyManager* enemy_manager = Engine::GetGameStateManager().GetGSComponent<EnemyManager>();
	std::vector<Enemy*>& enemies = enemy_manager->SetEnemies();
	std::vector<Item*>::iterator item_iter = std::find_if(use_items.begin(), use_items.end(),[](Item* item) {
		return item->Type() == GameObjectTypes::Axe;
		});
	if (item_iter != use_items.end()) {

		//attack_with_axe

		//get near_indices
		std::vector<Math::ivec2> near_indices;
		for (int i = GetIndex().x - 1; i <= GetIndex().x + 1; ++i) {
			for (int j = GetIndex().y - 1; j <= GetIndex().y + 1; ++j) {
				near_indices.push_back({ i,j });
			}
		}
		near_indices.erase(std::remove(near_indices.begin(), near_indices.end(), GetIndex()), near_indices.end());

		//destroy enemies
		bool did_axe_worked = false;
		int axe_killed_amount = 0;
		for (Enemy* enemy : enemies) {
			if (enemy->Type() == GameObjectTypes::Trap) {
				continue;
			}
			Math::ivec2 idx = enemy->GetIndex();
			for (int i = 0; i < near_indices.size(); ++i) {
				if (near_indices[i] == idx) {
					enemy->Defeated();
					//enemy_manager->EraseEnemy(enemy);
					used_item = true;
					is_moving = false;
					did_axe_worked = true;
					Engine::GetLogger().LogDebug("axe worked!");
					++axe_killed_amount;
					break;
				}
			}
		}
		/*======================================================================================*/
		if (did_axe_worked) {
			//Engine::GetLogger().LogDebug("axe killed" +std::to_string(axe_killed_amount) + "enemies!");
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			Axe* axe = static_cast<Axe*>(*(item_iter));
			--axe->SetLife();
			//item_manager->EraseUseItem(*item_iter);
			//use_items.erase(std::remove(use_items.begin(), use_items.end(), *(item_iter)), use_items.end());
			
		}		
		return;
	}
	item_iter = std::find_if(use_items.begin(), use_items.end(), [](Item* item) {
		return item->Type() == GameObjectTypes::Spear;
		});
	if (item_iter != use_items.end()) {
		//attack_with_spear

		//get near_indices
		std::vector<Math::ivec2> near_indices;
		switch (input)
		{
		case CS230::Input::Keys::A:
			near_indices.push_back({ GetIndex().x - 1, GetIndex().y - 1 });
			near_indices.push_back({ GetIndex().x - 1, GetIndex().y });
			near_indices.push_back({ GetIndex().x - 1, GetIndex().y + 1});
			break;
		case CS230::Input::Keys::D:
			near_indices.push_back({ GetIndex().x + 1, GetIndex().y - 1 });
			near_indices.push_back({ GetIndex().x + 1, GetIndex().y });
			near_indices.push_back({ GetIndex().x + 1, GetIndex().y + 1 });
			break;
		case CS230::Input::Keys::S:
			near_indices.push_back({ GetIndex().x - 1, GetIndex().y - 1 });
			near_indices.push_back({ GetIndex().x , GetIndex().y - 1 });
			near_indices.push_back({ GetIndex().x + 1, GetIndex().y - 1 });
			break;
		case CS230::Input::Keys::W:
			near_indices.push_back({ GetIndex().x - 1, GetIndex().y + 1 });
			near_indices.push_back({ GetIndex().x , GetIndex().y + 1 });
			near_indices.push_back({ GetIndex().x + 1, GetIndex().y + 1 });
			break;
		}
		
		//for (int i = GetIndex().x - 2; i <= GetIndex().x + 2; ++i) {
		//	for (int j = GetIndex().y - 2; j <= GetIndex().y + 2; ++j) {
		//		near_indices.push_back({ i,j });
		//	}
		//}
		//near_indices.erase(std::remove(near_indices.begin(), near_indices.end(), GetIndex()), near_indices.end());

		//destroy enemies
		bool did_spear_worked = false;
		for (Enemy* enemy : enemies) {
			
			Math::ivec2 idx = enemy->GetIndex();
			for (int i = 0; i < near_indices.size(); ++i) {
				if (near_indices[i] == idx) {
					enemy->Defeated();
					enemy_manager->EraseEnemy(enemy);
					used_item = true;
					is_moving = false;
					did_spear_worked = true;
					Engine::GetLogger().LogDebug("spear worked!");
					break;
				}
			}
			if (did_spear_worked == true) {
				break;
			}
		}
		/*=========================================================================================*/
		if (did_spear_worked == true) {
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attacking));
			Spear* spear = static_cast<Spear*>(*(item_iter));
			--spear->SetLife();
			//item_manager->EraseUseItem(*item_iter);
			//use_items.erase(std::remove(use_items.begin(), use_items.end(), *(item_iter)), use_items.end());
			
		}		
		return;
	}
}

void Player::EraseUseItem(Item* item) {
	item->Destroy();
	use_items.erase(std::remove(use_items.begin(), use_items.end(), item), use_items.end());
}