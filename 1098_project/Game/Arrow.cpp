#include "Arrow.h"
#include "Player.h"

Arrow::Arrow(Math::ivec2 index) :
	 Enemy(index)
{
	AddGOComponent(new CS230::Sprite("Assets/Arrow.spt", this));
}

void Arrow::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(1);
		did_attack = true;
		player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
	}
}
