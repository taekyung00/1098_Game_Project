#include "Tutorial.h"

Tutorial::Tutorial() :
	map_ptr(nullptr),
	player_ptr(nullptr)
{

}

void Tutorial::Load() {
	AddGSComponent(new TurnManager(MaxTurn, Turns::Player));
	AddGSComponent(new CS230::GameObjectManager());
	AddGSComponent(new EnemyManager());
	AddGSComponent(new ItemManager());
	//AddGSComponent(new SpawnTrap());
	map_ptr = new Map();
	GetGSComponent<CS230::GameObjectManager>()->Add(map_ptr);


	player_ptr = new Player();
	GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);
	GetGSComponent<CS230::GameObjectManager>()->Add(new Door({ 2,4 }));

	//GetGSComponent<SpawnTrap>()->SpawnTraps();
	GetGSComponent<EnemyManager>()->SpawnEnemiesTutorial();

	tutorial_audio_ptr = new Audio("Sounds/Drum,Metronom.mp3");
	tutorial_audio_ptr->SetLooping(true);
	AddGSComponent(tutorial_audio_ptr);
}

void Tutorial::Update(double dt) {
	EnemyManager* enemymanager = Engine::GetGameStateManager().GetGSComponent<EnemyManager>();
	std::vector<Enemy*>& enemies = enemymanager->SetEnemies();
	UpdateGSComponents(dt);
	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

	tutorial_audio_ptr->Update();
	enemymanager->TurnChange();
}

void Tutorial::Unload() {
	GetGSComponent<CS230::GameObjectManager>()->Unload();
	ClearGSComponents();
}

void Tutorial::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
}