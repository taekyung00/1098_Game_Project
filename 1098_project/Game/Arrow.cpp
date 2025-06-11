#include "Arrow.h"
#include "Player.h"

Arrow::Arrow(Math::ivec2 start_index, Math::ivec2 dest_index) :
	 Enemy(start_index)
{
	AddGOComponent(new CS230::Sprite("Assets/Arrow.spt", this));
	
	dest_pos = { start_position.x + dest_index.x * tile_size.x * scale_const.x , start_position.y + dest_index.y * tile_size.y * scale_const.y };
	//temp_pos = GetPosition();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
}

void Arrow::Update([[maybe_unused]] double dt) {
	GameObject::Update(dt);
	if (dest_pos != GetPosition())
	{
		if (dest_pos.x-GetPosition().x > 0) {
			UpdatePosition({ 150*dt,0 });
			if (dest_pos.x - GetPosition().x <= 10) {
				SetPosition({ dest_pos.x, GetPosition().y });
			}
		}
		else if (dest_pos.x - GetPosition().x < 0) {
			UpdatePosition({ -150 *dt,0 });
			if (dest_pos.x - GetPosition().x >= -10) {
				SetPosition({ dest_pos.x, GetPosition().y });
			}
		}

		if (dest_pos.y - GetPosition().y > 0) {
			UpdatePosition({ 0,150 *dt });
			if (dest_pos.y - GetPosition().y <= 10) {
				SetPosition({ GetPosition().x, dest_pos.y });
			}
		}
		else if (dest_pos.y - GetPosition().y < 0) {
			UpdatePosition({ 0,-150 * dt });
			if (dest_pos.y - GetPosition().y >= 10) {
				SetPosition({ GetPosition().x, dest_pos.y });
			}
		}
		
	}
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	if (turnmanager->GetCurrentTurn() == Turns::Player) {
		Destroy();
	}
}
void Arrow::ResolveCollision(GameObject* other_object) {
	TurnManager* turnmanager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
	if ((did_attack == false) && (other_object->Type() == GameObjectTypes::Player) && (turnmanager->GetCurrentTurn() == Turns::Enemy)) {
		turnmanager->Sub(3);
		did_attack = true;
		player->ChangeAnimation(static_cast<int>(Player::Animations::Attacked));
		Destroy();
	}
}
