
#include <iostream>

#include "InGame.h"


extern const Math::ivec2 tile_size = { 32,32 };
InGame::InGame() : 
	current_map_index(floor1_index), 
	map(), 
	player(turnmanager, map), 
	enemy(turnmanager, map, player), 
	audio("Sounds/Drum,Metronom.wav") {
	camera.target = { static_cast<float>(player.GetPosition().x),static_cast<float>(player.GetPosition().y) };
	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };

	camera.rotation = 0.f;
	camera.zoom = 1.f;
}

void InGame::Load() {
	traps.clear();
	map.Load();
	map.GetCurrentStage();
	for (Math::ivec2 index : trap_index[static_cast<int>(map.GetCurrentStage()) ]) {
		traps.push_back(new Trap(index));
	}
	for (Trap* trap : traps) {
		trap->Load();
	}
	turnmanager.Load();
	
	player.Load();
	enemy.Load();

	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
	audio.SetLooping(true);
	audio.Play();
}

void InGame::Update(double dt) {
	turnmanager.Update(dt);
	map.Update(dt);
	if (turnmanager.GetCurrentTurn() == TurnManager::Turns::player) {
		player.Update(dt, enemy);
	}
	else if(turnmanager.GetCurrentTurn() == TurnManager::Turns::enemy){
		enemy.Update(dt);
	}
	else if (turnmanager.GetCurrentTurn() == TurnManager::Turns::traps) {

		for (Trap* trap : traps) {
			trap->SetIsAlive() = !trap->SetIsAlive();
		}
	}
	//temperate collisioncheck
	
	for(Trap* trap: traps){
		trap->Update(dt);
		if (trap->GetIsAlive() == true) {
			if (CheckCollisionCircleRec({ static_cast<float>(player.GetPosition().x) ,static_cast<float>(player.GetPosition().y) }, player.GetRadius(), trap->GetTrapRect()) &&
				player.GetIsAttacked() == false) {
				player.SetMovingCount()--;
				player.SetIsAttacked() = true;
				Engine::GetLogger().LogDebug("player attacked!");
				turnmanager.SetCurrentTurn() =  TurnManager::Turns::enemy;
			}
		}
		
	}

	audio.Update();

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
		if (current_map_index == floor1_index) {
			current_map_index = floor2_index;
		}
		else if (current_map_index == floor2_index) {
			current_map_index = floor1_index;
		}
		Engine::GetGameStateManager().ReloadState();

	}
}

void InGame::Unload() {
	for (Trap* trap : traps) {
		delete trap;
	}
	map.Unload();
	player.Unload();
	enemy.Unload();
	audio.Stop();
}

void InGame::Draw() {
	BeginMode2D(camera);
	/*if (turnmanager.isplayerturn == true) {
		Engine::GetLogger().LogDebug("player turn");
	}
	else if (turnmanager.isenemyturn == true) {
		Engine::GetLogger().LogDebug("enemy turn");
	}*/
	Engine::GetLogger().LogDebug(std::to_string(enemy.GetArms().size()));
	Engine::GetWindow().Clear(0x00000000);
	map.Draw();
	
	for (Trap* trap : traps) {
		trap->Draw();
	}
	player.Draw();
	enemy.Draw();
	EndMode2D();
}

