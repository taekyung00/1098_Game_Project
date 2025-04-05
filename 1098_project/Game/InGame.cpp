#include "InGame.h"



InGame::InGame() : current_map_index(floor1_index),map(current_map_index), player(map),enemy(map,player){
	camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };

	camera.rotation = 0.f;
	camera.zoom = 1.f;
}

void InGame::Load(){
	isPlayerTurn = true;
	isEnemyTurn = false;
	map.Load(current_map_index);
	player.Load();
	enemy.Load();
	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
}

void InGame::Update(double dt){
	map.Update(current_map_index);
	if (isPlayerTurn) {
		player.Update(dt, enemy, isPlayerTurn, isEnemyTurn);
	}

	if (isEnemyTurn) {
		enemy.Update(dt, isEnemyTurn, isPlayerTurn);
	}

	if (player.GetTimeLimit() > 2) {
		camera.zoom = 1.f;
	}
	else if (player.GetTimeLimit() <= 2 && player.GetTimeLimit() > 1) {
		camera.zoom = 1.5f;
	}
	else {
		camera.zoom = 2.f;
	}
	camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
		Engine::GetGameStateManager().ReloadState();
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

void InGame::Unload(){
	map.Unload();
	player.Unload();
	enemy.Unload();
}

void InGame::Draw(){
	BeginMode2D(camera);
	if (isPlayerTurn == true) {
		Engine::GetLogger().LogDebug("player turn");
	}
	else if (isEnemyTurn == true) {
		Engine::GetLogger().LogDebug("enemy turn");
	}
	Engine::GetWindow().Clear(0xffffff00);
	map.Draw();
	player.Draw();
	enemy.Draw();

	EndMode2D();
}

