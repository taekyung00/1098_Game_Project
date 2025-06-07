#include "Player.h"

#include "Enemy.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "InGame.h"

Player::Player() :
	GameObject(Math::ivec2{2,0}, 0.0, scale_const)
{
	AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
	moving_sound_ptr = new Audio("Sounds/Moving_Sound.mp3");
	moving_sound_ptr->SetLooping(false);
	AddGOComponent(moving_sound_ptr);
	map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	after_move_timer = new CS230::Timer(0.0);
	AddGOComponent(after_move_timer);
}

void Player::Update([[maybe_unused]]double dt) {
	GameObject::Update(dt);
	moving_sound_ptr->Update();
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((turn_manager->GetCurrentTurn() == Turns::Player) && (turn_manager->GetTurnCount() > 0) &&(is_moving == true)) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
			if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isLeftEdge == false) {
				--SetIndex().x;
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}
				

			}
			else {
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}

			}
		}
		else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
			if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isBottomEdge == false) {
				--SetIndex().y;
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}
			}
			else {
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}
			}
		}
		else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
			if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isRightEdge == false) {
				++SetIndex().x;
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}

			}
			else {
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}

			}
		}
		else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
			if (map->GetTileDesign()[GetIndex().x][GetIndex().y].isTopEdge == false) {
				++SetIndex().y;
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}

			}
			else {
				turn_manager->Sub();
				is_moving = false;
				moving_sound_ptr->Play();
				if (InGame::GetEnemies().size() == 0) {
					after_move_timer->Set(0.05);
				}
				else {
					after_move_timer->Set(after_move_time);
				}

			}
		}
		
	}
	if ((is_moving == false) && (turn_manager->GetCurrentTurn() == Turns::Player) && (turn_manager->GetTurnCount() > 0) &&(after_move_timer->Remaining()==0.0)) {
		is_moving = true;
		if (InGame::GetEnemies().size() != 0) {
			++(turn_manager->SetCurrentTurn());
		}
			
	}
	SetPosition({ start_position.x + GetIndex().x * tile_size.x * scale_const.x, start_position.y + GetIndex().y * tile_size.y * scale_const.y });
}

void Player::Draw(Math::TransformationMatrix camera_matrix) {
	CS230::GameObject::Draw(camera_matrix);
}

bool Player::CanCollideWith(GameObjectTypes other_object_type) {

	if (Engine::GetGameStateManager().GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Player) {
		if (other_object_type == GameObjectTypes::Door) {
			return true;
		}
		else if (other_object_type == GameObjectTypes::Enemy) {
			return true;
		}
	}
	
	return false;
}

void Player::ResolveCollision(GameObject* other_object) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	switch (other_object->Type())
	{
	case GameObjectTypes::Door:
		if (!(map->GetStage() == Stages::stage3 && map->GetRoom() == Rooms::Room3)) {
			turn_manager->SetCurrentTurn() = Turns::Player;
			if (map->GetRoom() == Rooms::Room3) {
				++map->SetStage();
			}
			++map->SetRoom();
			
			SetIndex() = start_index;
			map->InitializeStage(map->GetStage());
			Engine::GetGameStateManager().GetGSComponent<SpawnEnemy>()->SpawnEnemies(InGame::SetEnemies());
			InGame::ChangeAudio();
			is_moving = true;
			
		}
		else {
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
		}
		break;
	case GameObjectTypes::Enemy:
		turn_manager->Add(5);
		other_object->Destroy();
		Engine::GetLogger().LogDebug("enemy is destroyed!");
		std::vector<Enemy*>& enemies = InGame::SetEnemies();
		enemies.erase(std::remove(enemies.begin(), enemies.end(), other_object), enemies.end());
		break;
	}
}

