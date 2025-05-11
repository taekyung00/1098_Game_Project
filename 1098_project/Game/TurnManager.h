#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#pragma once

class TurnManager {
public:
	TurnManager();
	void Load();
	void Update(double dt);
	void PlayerToEnemy();
	void EnemyToPlayer();
	void Unload();

private:
	static constexpr double max_player_turn_count = 3.0;
	static constexpr double max_enemy_turn_count = 0.5;


	double player_turn_count;
	double enemy_turn_count;
public:
	bool isplayerturn = true;
	bool isenemyturn = false;
};
#endif // !TURNMANAGER_H


