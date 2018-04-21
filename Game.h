/***********************************************************************************
File Name: Game.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Game - container object for program data
Procedures: bool Load() - pushes commands to command list, calls other load functions
			bool LoadScenes() - reads scenes from text file, adds to scenes list
			bool LoadRooms() - reads rooms from text file, adds to rooms list
			bool LoadEntities() - reads entities from text file, adds to entities list
			bool LoadItems() - reads items from text file, adds to items list
			bool findItem(string itemName) - checks items list for item by full name
			Item getItem(string itemName) - returns item from full name
			bool findEntity(string entityName) - checks entity list for entity by name
			Entity getEntity(string entityName) - returns entity matching name
			string makeLower(string str) - returns lowercase version of string
			bool SaveGame(string filename) - saves player data to file
			Scene* nextScene() - gets next scene
			void battle() - executes battle sequence
			Game() - construct game object
			~Game() - destruct game object
			void Play(string filename) - executes game playing
			bool IsLoaded() - returns whether game data loaded successfully
			void NewGame(string playerName) - creates new game
			bool LoadGame(string playerName) - tries to load game/player data
************************************************************************************/
#pragma once

#include <string>

#include "Scene.h"
#include "Move.h"
#include "Get.h"
#include "Help.h"
#include "Use.h"
#include "Look.h"
#include "Entity.h"

class Game
{
private:
	Move move_cmd;
	Get get_cmd;
	Help help_cmd;
	Use use_cmd;
	Look look_cmd;
	vector<Command*> commands;	// list of all commands available
	vector<Scene> scenes;		// list of all scenes
	vector<Item> items;			// list of all items in game
	vector<Entity> entities;    // list of all entities in game
	Player player;				// player
	Scene* currentScene;
	bool loaded;
	bool Load();
	bool LoadScenes();
	bool LoadRooms();
	bool LoadEntities();
	bool LoadItems();
	bool findItem(string itemName);
	Item getItem(string itemName);
	bool findEntity(string entityName);
	Entity getEntity(string entityName);
	string makeLower(string str);
	bool SaveGame(string filename);
	Scene* nextScene();
	void battle();
public:
	Game();
	~Game();
	void Play(string filename);
	bool IsLoaded();
	void NewGame(string playerName);
	bool LoadGame(string playerName);
};

