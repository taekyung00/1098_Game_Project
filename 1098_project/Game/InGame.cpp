
#include <iostream>

#include "InGame.h"


extern const Math::ivec2 tile_size = { 32,32 };
extern const Math::ivec2 start_position = { 50,50 };
InGame::InGame() : 
	//current_map_index(floor1_index), 
	map(), 
	player(turnmanager, map), 
	//enemy(turnmanager, map, player), 
<<<<<<< Updated upstream
	audio("Sounds/Drum,Metronom.mp3") ,
	collisionmanager(player,enemies)
=======
	stage1_audio("Sounds/Drum,Metronom.mp3"),
	stage2_audio("Sounds/Forest_bgm_final.mp3"),
	stage3_audio("Sounds/Castle_bgm_final.mp3"),
	collisionmanager(map,player,enemies,traps)
>>>>>>> Stashed changes
{
	Enemy::SetPlayerReference(player);
	Enemy::SetMapReference(map);
	camera.target = { static_cast<float>(player.GetPosition().x),static_cast<float>(player.GetPosition().y) };
	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };

	camera.rotation = 0.f;
	camera.zoom = 1.f;
}

void InGame::Load() {
	enemies.clear();
	traps.clear();
	map.Load();
	map.GetCurrentStage();
	enemies.push_back(new Pawn({ 2,6 },"Assets/pawn.png"));
	player.SetEnemiesReference(enemies);
	for (Math::ivec2 index : trap_index[static_cast<int>(map.GetCurrentStage()) ]) {
		traps.push_back(new Trap(index));
	}
	for (Trap* trap : traps) {
		trap->Load();
	}
	turnmanager.Load();
	
	player.Load();
	//enemy.Load();

	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
<<<<<<< Updated upstream
	audio.SetLooping(true);
	audio.Play();
=======
	camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
	stage1_audio.SetLooping(true);
	stage2_audio.SetLooping(true);
	stage3_audio.SetLooping(true);
	if (map.GetCurrentStage() == Stages::stage1)
	{
		stage1_audio.Play();
	}
	else if (map.GetCurrentStage() == Stages::stage2)
	{
		stage2_audio.Play();
	}
	else if (map.GetCurrentStage() == Stages::stage3)
	{
		stage3_audio.Play();
	}
>>>>>>> Stashed changes
}

void InGame::Update(double dt) {
	turnmanager.Update(dt);
	map.Update(dt);
	if (turnmanager.GetCurrentTurn() == TurnManager::Turns::player) {
		for (Enemy* enemy : enemies) {
			enemy->SetIsOutdated() = true;
		}
		for (Trap* trap : traps) {
			trap->SetIsOutdated() = true;
		}
		player.Update(dt);
	}
	else if(turnmanager.GetCurrentTurn() == TurnManager::Turns::enemy){
		for (Enemy* enemy : enemies) {
			enemy->Update(dt);
		}
	}
	
	else if (turnmanager.GetCurrentTurn() == TurnManager::Turns::traps) {
		
		for (Trap* trap : traps) {
			trap->Update(dt);
		}
	}
	collisionmanager.CollisionCheck();
	//temperate collisioncheck
	
	for(Trap* trap: traps){
		if (trap->GetIsAlive() == true) {
			if (CheckCollisionRecs(player.GetPlayerRect(), trap->GetTrapRect()) &&
				player.GetIsAttacked() == false) {
				player.SetMovingCount()--;
				player.SetIsAttacked() = true;
				Engine::GetLogger().LogDebug("player attacked!");
				turnmanager.SetCurrentTurn() =  TurnManager::Turns::enemy;
			}
		}
		
	}

	if (map.GetCurrentStage() == Stages::stage1)
	{
		stage1_audio.Update();
	}
	else if (map.GetCurrentStage() == Stages::stage2)
	{
		stage2_audio.Update();
	}
	else if (map.GetCurrentStage() == Stages::stage3)
	{
		stage3_audio.Update();
	}

	if (player.GetTimeLimit() > 2) {
		camera.zoom = 2.f;
	}
	else if (player.GetTimeLimit() <= 2 && player.GetTimeLimit() > 1) {
		camera.zoom = 3.f;
	}
	else {
		camera.zoom = 4.f;
	}
	camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
		Engine::GetGameStateManager().ReloadState();
		std::cout << "RR\n";
	}

	if (player.GetCurrentIndex() == map.GetExitIndex()) {
		Engine::GetGameStateManager().ReloadState();

	}
}

void InGame::Unload() {
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
	for (Trap* trap : traps) {
		delete trap;
	}
	traps.clear();
	map.Unload();
	player.Unload();
	//enemy.Unload();
	if (map.GetCurrentStage() == Stages::stage1)
	{
		stage1_audio.Stop();
	}
	else if (map.GetCurrentStage() == Stages::stage2)
	{
		stage2_audio.Stop();
	}
	else if (map.GetCurrentStage() == Stages::stage3)
	{
		stage3_audio.Stop();
	}
}

void InGame::Draw() {
	BeginMode2D(camera);
	/*if (turnmanager.isplayerturn == true) {
		Engine::GetLogger().LogDebug("player turn");
	}
	else if (turnmanager.isenemyturn == true) {
		Engine::GetLogger().LogDebug("enemy turn");
	}*/
	//Engine::GetLogger().LogDebug(std::to_string(enemy.GetArms().size()));
	Engine::GetWindow().Clear(0x00000000);
	map.Draw();
	
	for (Trap* trap : traps) {
		trap->Draw();
	}
	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}
	player.Draw();
	//enemy.Draw();
	EndMode2D();
}

