#include "Pawn.h"
#include "Rook.h"
#include "TurnManager.h"

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

void Pawn::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(1);
		did_attack = true;
	}
}