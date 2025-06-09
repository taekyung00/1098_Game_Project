#include "Player.h"
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
		push_button_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Push WASD To Move", 0xFFFFFFFF);

	}
	else if (GetGSComponent<TurnManager>()->GetCurrentTurn() == Turns::Enemy) {
		turn_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Enemy Turn", 0xFFFFFFFF);
		push_button_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Push SPACE To Change Turn", 0xFFFFFFFF);
	}
}

InGame::InGame() :
	turncount_texture(nullptr),
	turn_texture(nullptr),
	push_button_texture(nullptr),
	map_ptr(nullptr),
	player_ptr(nullptr)
{
}

void InGame::Load() {
	
	AddGSComponent(new TurnManager(MaxTurn,Turns::Player));
	AddGSComponent(new CS230::GameObjectManager());
	AddGSComponent(new EnemyManager());
	AddGSComponent(new ItemManager());
	//AddGSComponent(new SpawnTrap());
	map_ptr = new Map(/*Stages::stage1,Rooms::Store*/);
	GetGSComponent<CS230::GameObjectManager>()->Add(map_ptr);
	

	player_ptr = new Player();
	GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);
	GetGSComponent<CS230::GameObjectManager>()->Add(new Door({2,4}));
	
	//GetGSComponent<SpawnTrap>()->SpawnTraps();
	GetGSComponent<EnemyManager>()->SpawnEnemies();	

	stage1_audio_ptr = new Audio("Sounds/Drum,Metronom.mp3");
	stage1_audio_ptr->SetLooping(true);
	AddGSComponent(stage1_audio_ptr);

	stage2_audio_ptr = new Audio("Sounds/Forest_bgm_final.mp3");
	stage2_audio_ptr->SetLooping(true);
	AddGSComponent(stage2_audio_ptr);

	stage3_audio_ptr = new Audio("Sounds/Castle_bgm_final.mp3");
	stage3_audio_ptr->SetLooping(true);
	AddGSComponent(stage3_audio_ptr);

	current_audio_ptr = stage1_audio_ptr;
	current_audio_ptr->Play();

	update_turncount_text();
	update_turn_text();
}

void InGame::Update(double dt) {
	map_ptr->ClearEnemiesReachable();
	EnemyManager* enemymanager = Engine::GetGameStateManager().GetGSComponent<EnemyManager>();
	//std::vector<Enemy*>& enemies = enemymanager->SetEnemies();
	UpdateGSComponents(dt);
	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
	
	update_turncount_text();
	update_turn_text();
	Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->SortForDraw();
	current_audio_ptr->Update();
	enemymanager->TurnChange();
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
	//Engine::GetGameStateManager().GetGSComponent<EnemyManager>()->ClearEnemies();

}

void InGame::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());
	turncount_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - turncount_texture->GetSize().x, Engine::GetWindow().GetSize().y - turncount_texture->GetSize().y - 5 }));
	turn_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - turn_texture->GetSize().x, Engine::GetWindow().GetSize().y - turn_texture->GetSize().y - 15 - turncount_texture->GetSize().y }));
	push_button_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - push_button_texture->GetSize().x, push_button_texture->GetSize().y}));
}

void InGame::ChangeAudio()
{
	current_audio_ptr->Stop();
	Map* static_map_ptr = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Map>();
	if (static_map_ptr->GetStage() == Stages::stage1) {
		current_audio_ptr = stage1_audio_ptr;
	}
	else if (static_map_ptr->GetStage() == Stages::stage2) {
		current_audio_ptr = stage2_audio_ptr;
	}
	else if (static_map_ptr->GetStage() == Stages::stage3) {
		current_audio_ptr = stage3_audio_ptr;
	}
	current_audio_ptr->Play();
}

