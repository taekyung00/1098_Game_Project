#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#pragma once

class TurnManager {
public:
	enum class Turns
	{
		player,
		enemy,
		traps
	};
	TurnManager();
	void Load();
	void Update(double dt);
	/*void PlayerToEnemy();
	void EnemyToPlayer();*/
	void CountReset();
	//const double& GetPlayerTurnCount() const { return player_turn_count; }
	const double& GetEnemyTurnCount() const { return enemy_turn_count; }
	const double& GetTrapTurnCount() const { return trap_turn_count; }
	const Turns& GetCurrentTurn() const { return current_turn; }
	Turns& SetCurrentTurn() { return current_turn; }
	void Unload();

private:
	

	Turns current_turn;
	//static constexpr double max_player_turn_count = 3.0;
	static constexpr double max_enemy_turn_count = 0.3;
	static constexpr double max_trap_turn_count = 0.3;


	//double player_turn_count;
	double enemy_turn_count;
	double trap_turn_count;
//public:
//	bool isplayerturn = true;
//	bool isenemyturn = false;
};
#endif // !TURNMANAGER_H


