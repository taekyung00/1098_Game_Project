#pragma once
#include <random> // for std::random_device, std::mt19937
#include <algorithm> // for std::shuffle
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "..\Engine\GameObject.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "GameObjectTypes.h"
#include "Stages.h"
#include "Rooms.h"
#include "Tile.h"



class Map : public CS230::GameObject {
public:
	Map(Stages start_stage = Stages::stage1, Rooms start_room = Rooms::Room1);
	void			Update(double dt) override;
	void			Draw(Math::TransformationMatrix camera_matrix) override;
	GameObjectTypes Type() override { return GameObjectTypes::Map; }
	std::string		TypeName() override { return "Map"; }
	
	//int DrawPriority() const override { return 0; }

	const std::vector<std::vector<Tile>>&	GetTileDesign() const { return tile_design; }
	std::vector<std::vector<Tile>>&			SetTileDesign() { return tile_design; }

	const Stages	GetStage() const { return stage; }
	Stages&			SetStage() { return stage; }

	void			InitializeStage(Stages _stage = Stages::stage1);

	const Rooms		GetRoom() const { return room; }
	Rooms&			SetRoom() { return room; }

	//void ClearEnemiesReachable();
	const std::vector<std::vector<int>>& GetSpawnLayer() const { return spawn_layer; }
	const std::vector<std::vector<int>>& GetSpawnTrapLayer() const { return spawn_trap_layer; }
	
private:
	
	Math::ivec2 current_index_amount;
	Math::ivec2 grid_size;

	std::vector<std::vector<Tile>> tile_design;

	int width_amount = 0;
	int height_amount = 0;

	CS230::Sprite enemy_trajectory;
	bool enemy_trajectory_draw = false;
	std::string designPath;
	std::vector<std::string> availablefiles;
	std::vector<std::string> selectedfiles;
	size_t currentmapindex = 0;
	std::vector<std::vector<int>> spawn_layer;
	std::vector<std::vector<int>> spawn_trap_layer;

	Stages stage;
	Rooms room;
};
