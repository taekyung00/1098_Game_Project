#include "Merchant.h"
#include "Map.h"

Merchant::Merchant(Math::ivec2 index) :
	GameObject(index,0.0, scale_const),
	merchant_carpet("Assets/MerchantCarpet.spt", this)
{
	AddGOComponent(new CS230::Sprite("Assets/Merchant.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
}

void Merchant::Update([[maybe_unused]] double dt) {
	GameObject::Update(dt);
	Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	if (map->GetRoom() != Rooms::Store) {
		Destroy();
	}
}

void Merchant::Draw(Math::TransformationMatrix camera_matrix) {
	
	if (Destroyed() == false) {
		merchant_carpet.Draw(camera_matrix* GetMatrix());
	}
	GameObject::Draw(camera_matrix);
}
