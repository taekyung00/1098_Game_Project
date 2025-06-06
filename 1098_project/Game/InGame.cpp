#include "InGame.h"


void InGame::update_turncount_text()
{
	delete turncount_texture;
	turncount_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Turn: " + std::to_string(GetGSComponent<TurnManager>()->GetTurnCount()), 0xFFFFFFFF);
}
void InGame::update_turn_text()
{
	delete turn_texture;
	delete push_button_texture;
	if (GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Player) {
		turn_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Player Turn", 0xFFFFFFFF);
		push_button_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Push TAB After Move", 0xFFFFFFFF);

	}
	else if (GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Enemy) {
		turn_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Enemy Turn", 0xFFFFFFFF);
		push_button_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Push SPACE After Move", 0xFFFFFFFF);
	}
}
InGame::InGame() :
	turncount_texture(nullptr),
	turn_texture(nullptr),
	map_ptr(nullptr),
	player_ptr(nullptr)
{
}

void InGame::Load() {
	AddGSComponent(new TurnManager(max_turn,Turns::Player));
	AddGSComponent(new CS230::GameObjectManager());
	AddGSComponent(new SpawnEnemy());
	map_ptr = new Map();
	GetGSComponent<CS230::GameObjectManager>()->Add(map_ptr);
	player_ptr = new Player({ 3,3 });
	GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);
	GetGSComponent<CS230::GameObjectManager>()->Add(new Door({2,4}));
	GetGSComponent<SpawnEnemy>()->SpawnEnemies(enemies);
	

	update_turncount_text();
	update_turn_text();
}

void InGame::Update(double dt) {
	//Map* map = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	//map->ClearEnemiesReachable();
	UpdateGSComponents(dt);
	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
	update_turncount_text();
	update_turn_text();

	bool are_enemies_all_outdated = true;
	for (Enemy* enemy : enemies) {
		if (enemy->GetIsOutdated() == false) {
			are_enemies_all_outdated = false;
			break;
		}
	}
	TurnManager* turn_manager = Engine::GetGameStateManager().GetGSComponent<TurnManager>();
	Turns current_turn = turn_manager->GetCurrentTurn();
	if (current_turn == Turns::Enemy&& are_enemies_all_outdated == true) {
		turn_manager->SetCurrentTurn() = Turns::Player;
	}

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

void InGame::Unload() {
	GetGSComponent<CS230::GameObjectManager>()->Unload();
	ClearGSComponents();
	delete turncount_texture;
	turncount_texture = nullptr;
	delete turn_texture;
	turn_texture = nullptr;
	delete push_button_texture;
	push_button_texture = nullptr;

}

void InGame::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
	turncount_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - turncount_texture->GetSize().x, Engine::GetWindow().GetSize().y - turncount_texture->GetSize().y - 5 }));
	turn_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - turn_texture->GetSize().x, Engine::GetWindow().GetSize().y - turn_texture->GetSize().y - 15 - turncount_texture->GetSize().y }));
	push_button_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - push_button_texture->GetSize().x, push_button_texture->GetSize().y}));
}

