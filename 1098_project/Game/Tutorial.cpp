#include "Tutorial.h"

Tutorial::Tutorial() :
	map_ptr(nullptr),
	player_ptr(nullptr),
	turncount_texture(nullptr),
	//turn_texture(nullptr),
	push_button_texture(nullptr)
{

}
void Tutorial::update_turncount_text()
{
	delete turncount_texture;
	turncount_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Turn: " + std::to_string(GetGSComponent<TurnManager>()->GetTurnCount()), 0xFFFFFFFF);
}
void Tutorial::update_turn_text()
{
	//delete turn_texture;
	delete push_button_texture;
	if (GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Player) {
		//turn_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Player Turn", 0xFFFFFFFF);
		push_button_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Push WASD To Move", 0xFFFFFFFF);

	}
	else if (GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Enemy) {
		//turn_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Enemy Turn", 0xFFFFFFFF);
		push_button_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Please Wait To Change Turn", 0xFFFFFFFF);
	}
}
void Tutorial::Load() {
	InitAudioDevice();
	AddGSComponent(new TurnManager(MaxTurn, Turns::Player));
	AddGSComponent(new CS230::GameObjectManager());
	AddGSComponent(new EnemyManager());
	AddGSComponent(new ItemManager());
	//AddGSComponent(new SpawnTrap());
	map_ptr = new Map(Stages::Tutorial);
	GetGSComponent<CS230::GameObjectManager>()->Add(map_ptr);


	player_ptr = new Player();
	GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);
	GetGSComponent<CS230::GameObjectManager>()->Add(new Door({ 2,4 }));
	AddGSComponent(new UI());

	//GetGSComponent<SpawnTrap>()->SpawnTraps();
	GetGSComponent<EnemyManager>()->SpawnEnemies();

	tutorial_audio_ptr = new Audio("Sounds/Drum,Metronom.mp3");
	tutorial_audio_ptr->SetLooping(true);
	AddGSComponent(tutorial_audio_ptr);

	current_audio_ptr = tutorial_audio_ptr;
	current_audio_ptr->Play();
}

void Tutorial::Update(double dt) {
	map_ptr->ClearEnemiesReachable();
	current_audio_ptr->Update();
	EnemyManager* enemymanager = Engine::GetGameStateManager().GetGSComponent<EnemyManager>();
	//std::vector<Enemy*>& enemies = enemymanager->SetEnemies();
	UpdateGSComponents(dt);
	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
	update_turncount_text();
	update_turn_text();
	Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->SortForDraw();
	enemymanager->TurnChange();
	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}

void Tutorial::Unload() {
	tutorial_audio_ptr->Stop();
	GetGSComponent<CS230::GameObjectManager>()->Unload();
	ClearGSComponents();
	delete turncount_texture;
	turncount_texture = nullptr;
	//delete turn_texture;
	//turn_texture = nullptr;
	delete push_button_texture;
	push_button_texture = nullptr;
	
}

void Tutorial::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
	GetGSComponent<UI>()->Draw();
	turncount_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - turncount_texture->GetSize().x, Engine::GetWindow().GetSize().y - turncount_texture->GetSize().y - 5 }));
	//turn_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - turn_texture->GetSize().x, Engine::GetWindow().GetSize().y - turn_texture->GetSize().y - 15 - turncount_texture->GetSize().y }));
	push_button_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 0, Engine::GetWindow().GetSize().y - push_button_texture->GetSize().y }));
}
