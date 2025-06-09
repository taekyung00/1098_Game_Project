#include "Pawn.h"
#include "Rook.h"
#include "TurnManager.h"
#include "Player.h"

Pawn::Pawn(Math::ivec2 index) :
	Enemy(index) ,
	movable("Assets/Movable.spt", this)
{
	AddGOComponent(new CS230::Sprite("Assets/Pawn.spt", this));
	ReachableIndexPush();
	//ChangeMapDesign();
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
	movable.Draw(camera_matrix * GetMatrix());
}

void Pawn::attack() {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(1);
		did_attack = true;
		player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
	}
}