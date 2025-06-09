#include "Player.h"

#include "Enemy.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "EnemyManager.h"
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
	if ((turn_manager->GetCurrentTurn() == Turns::Player)) {
		if ((turn_manager->GetTurnCount() > 0) && (is_moving == true)) {
			if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
				move_left();
			}
			else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
				move_bottom();
			}
			else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
				move_right();
			}
			else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
				move_top();
			}

		}
		if ((is_moving == false) && (turn_manager->GetTurnCount() > 0)   /*&&(after_move_timer->Remaining()==0.0)*/) {
			if (did_nothing == false && GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
				GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
				is_moving = true;
				if (!((enemies.size() == 0) || ((enemies.size() == 1) && (enemies[0]->Type() == GameObjectTypes::Trap)))) {
					(turn_manager->SetCurrentTurn()) = Turns::Enemy;
				}
			}
			else if (did_nothing == true) {
				is_moving = true;
				did_nothing = false;
				if (!((enemies.size() == 0) || ((enemies.size() == 1) && (enemies[0]->Type() == GameObjectTypes::Trap)))) {
					(turn_manager->SetCurrentTurn()) = Turns::Enemy;
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
		map->ChangeStageAndRoom();
		if (!(map->GetStage() == Stages::End && map->GetRoom() == Rooms::Count)) {
			turn_manager->SetCurrentTurn() = Turns::Player;

			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
			SetIndex() = start_index;
			map->InitializeStage(map->GetStage());
			
			
			Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->SpawnEnemies();
			Engine::GetGameStateManager().GetGSComponent<ItemManager>()->ClearDropItem();
			
			InGame::ChangeAudio();
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

void Player::move_left()
{
	EnemyManager* enemy_manager = Engine::GetGameStateManager().GetGSComponent<EnemyManager>();
	std::vector<Enemy*>& enemies = enemy_manager->SetEnemies();
	if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isLeftEdge == false) {
		bool enemy_attacked = false;
		for (Enemy* enemy : enemies) {
			if ((enemy->Type() == GameObjectTypes::Enemy) && (Math::ivec2{ GetIndex().x - 1, GetIndex().y } == enemy->GetIndex())) {
				enemy_attacked = true;
				Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(enemy->GetIndex());
				enemy->Destroy();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				enemy_manager->EraseEnemy(enemy);
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
	turn_manager->Sub();
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
				Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(enemy->GetIndex());
				enemy->Destroy();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
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
	turn_manager->Sub();
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
				Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(enemy->GetIndex());
				enemy->Destroy();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
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
	turn_manager->Sub();
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
				Engine::GetGameStateManager().GetGSComponent<ItemManager>()->DropItem(enemy->GetIndex());
				enemy->Destroy();
				Engine::GetLogger().LogDebug("enemy is destroyed!");
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
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
	turn_manager->Sub();
	is_moving = false;
	moving_sound_ptr->Play();
}

