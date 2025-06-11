#include "Enemy.h"
#include "EnemyManager.h"
#include "Player.h"

Enemy::Enemy(Math::ivec2 start_index) : 
	GameObject(start_index, 0.0, scale_const)
{
	turn_timer = new CS230::Timer(0.0);
	AddGOComponent(turn_timer);
}

void Enemy::Update([[maybe_unused]]double dt) {
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
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
void Enemy::ChangeIndex()
{
	Math::ivec2 new_index = GetIndex();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	const std::vector<Enemy*>& enemies = Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->GetEnemies();
	bool is_player_in_reachable = false;
	for (Math::ivec2 _index : reachable_indices) {
		if (_index == player->GetIndex()) {
			is_player_in_reachable = true;
			reachable_indices.erase(std::remove(reachable_indices.begin(), reachable_indices.end(), _index), reachable_indices.end());
		}
	}
	if (is_player_in_reachable == true) {
		attack();
	}
	for(Math::ivec2 _index : reachable_indices) {
		if (Math::GetDistanceSquaredBetweenIndices(new_index, player->GetIndex()) > Math::GetDistanceSquaredBetweenIndices(_index, player->GetIndex())) {
			bool index_over = false;
			for (Enemy* enemy : enemies) {
				if (_index == enemy->GetIndex()) {
					index_over = true;
					break;
				}
			}
			if (index_over == false) {
				new_index = _index;
			}
			
		}
	}
	SetIndex() = new_index;
}

void Enemy::attack()
{
}

void Enemy::ChangeMapDesign() {
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	for (Math::ivec2 _index : reachable_indices) {
		map->SetTileDesign()[_index.x][_index.y].isEnemyReachable = true;
	}
	//map_changed = true;
}

bool Enemy::CanCollideWith(GameObjectTypes other_object_type) {
	if (Engine::GetGameStateManager().GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Enemy && other_object_type == GameObjectTypes::Player) {
		return true;
	}
	return false;
}

//void Enemy::ResolveCollision(GameObject* other_object) {
//	other_object->Destroy();
//	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
//}