#include "InGame.h"



InGame::InGame() : current_map_index(floor1_index), map(current_map_index), player(turnmanager, map), enemy(turnmanager, map, player), audio("Sounds/Drum,Metronom.wav") {
	camera.target = { float(player.GetPosition().x),float(player.GetPosition().y) };
	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };

	camera.rotation = 0.f;
	camera.zoom = 1.f;
}

void InGame::Load() {
	turnmanager.Load();
	map.Load(current_map_index);
	player.Load();
	enemy.Load();
	camera.offset = { Engine::GetWindow().GetSize().x / 2.f ,Engine::GetWindow().GetSize().y / 2.f };
	audio.SetLooping(true);
	audio.Play();
}

void InGame::Update(double dt) {
	turnmanager.Update(dt);
	map.Update(current_map_index);
	if (turnmanager.isplayerturn) {
		player.Update(dt, enemy, turnmanager.isplayerturn, turnmanager.isenemyturn);
	}

	if (turnmanager.isenemyturn) {
		enemy.Update(dt, turnmanager.isenemyturn, turnmanager.isplayerturn);
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
	map.Unload();
	player.Unload();
	enemy.Unload();
	audio.Stop();
}

void InGame::Draw() {
	BeginMode2D(camera);
	if (turnmanager.isplayerturn == true) {
		Engine::GetLogger().LogDebug("player turn");
	}
	else if (turnmanager.isenemyturn == true) {
		Engine::GetLogger().LogDebug("enemy turn");
	}
	Engine::GetWindow().Clear(0x00000000);
	map.Draw();
	player.Draw();
	enemy.Draw();

	EndMode2D();
}

