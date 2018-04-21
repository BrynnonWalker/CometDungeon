/***********************************************************************************
File Name: Game.cpp
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
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Game.h"
/***********************************************************************************
Function: Game
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Construct game object
Arguments:	none
************************************************************************************/
Game::Game()
{
	// load game
	if (Load())
	{
		// game loaded
		// build scene map for each scene
		loaded = true;
		for (size_t i = 0; i < scenes.size() && loaded; i++)
		{
			cout << "building scene: " << scenes.at(i).getRoomFilename() << endl;
			loaded = scenes.at(i).buildMap();
		}
    
		if (!loaded)
		{
			// scenes not fully loaded!
			cout << "Error building scenes." << endl;
		}/*
		else
		{
			cout << "Scenes loaded." << endl;
			// scenes loaded, display map
			for (size_t i = 0; i < scenes.size(); i++)
			{

				scenes.at(i).showMap();
			}
		}*/
	}
	else
	{
		// game not fully loaded!
		cout << "Error loading game data." << endl;
		loaded = false;
	}
}
/***********************************************************************************
Function: ~Game
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Destruct game object
Arguments:	none
************************************************************************************/
Game::~Game()
{
}
/***********************************************************************************
Function: LoadScenes
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Reads scenes from text file and adds the scenes to scenes list
Arguments:	(O/P) bool - whether it loaded sucessfully
************************************************************************************/
bool Game::LoadScenes()
{
	string filename = "scenes.txt";
	fstream file(filename, ios::in);

	// check if opened
	if (file)
	{
		cout << "Loading scenes." << endl;

		// opened
		string read = "";
		bool reading = false;
		Scene temp;

		while (!file.eof())
		{
			// read file
			getline(file, read);

			// check for new line character on string
			if(read.length() > 2 && !isalnum(read.back()))
			{
				// the compiler is adding on the newline char to string!
				// pull it off!
				read = read.substr(0,read.length()-1);
			}

			// check for start/end of scene
			if (!reading && read.compare("NEW") == 0)
			{
				// new scene
				reading = true;
			}
			
			if (reading && read.compare("END") == 0)
			{
				// end scene
				reading = false;
				// add scene to game's scenes
				scenes.emplace_back(temp);
				temp.clear();
			}

			// reading scene
			if (reading && read.find_first_of("|") != string::npos)
			{
				// currently reading in scene data
				// check for various parts of scene
				if (read.substr(0, read.find_first_of("|")).compare("ID") == 0)
				{
					// currently reading in ID
					temp.setName(read.substr(read.find_first_of("|") + 1));
				}
				if (read.substr(0, read.find_first_of("|")).compare("ORDER") == 0)
				{
					// currently reading in order of scene
					temp.setOrder(atoi(read.substr(read.find_first_of("|") + 1).c_str()));
				}
			}
		}

                file.close();

	}
	else
	{
		// file didn't open!
		cout << "Could not load scenes." << endl;
		return false;
	}

	// check that at least one scene was loaded
	if (scenes.empty())
	{
		cout << "No scenes loaded!" << endl;
		return false;
	}

	// check scene orders
	for (size_t i = 0; i < scenes.size(); i++)
	{
		for (size_t j = 0; j < scenes.size(); j++)
		{
			if (i != j && scenes.at(i).getOrder() == scenes.at(j).getOrder())
			{
				// two scenes have same order!
				cout << "Two scenes have the same order." << endl;
				return false;
			}
		}
	}

	return true;
}
/***********************************************************************************
Function: LoadRooms
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Reads rooms from text file, adds to rooms list
Arguments:	(O/P) bool - whether it loaded sucessfully
************************************************************************************/
bool Game::LoadRooms()
{
	fstream file;
	string read, tempStr;
	bool reading = false;
	Room temp;
	Entity tempEnt;
	Item tempItem;
	Pathway tempPath;
	int multiCount = 0;

	// for each scene
	for (size_t i = 0; i < scenes.size(); i++)
	{
		// open scene's rooms and add them
		file.open(scenes.at(i).getRoomFilename(), ios::in);
		if (file)
		{

			cout << "Adding rooms to scene.." << endl;
			cout << scenes.at(i).getRoomFilename() << endl;

			// file opened
			while (!file.eof())
			{
				// read file
				getline(file, read);

				// check for new line character on string
				if(read.length() > 2 && !isalnum(read.back()))
				{
					// the compiler is adding on the newline char to string!
					// pull it off!
					read = read.substr(0,read.length()-1);
				}

				// check for start/end of room
				if (!reading && read.compare("NEW") == 0)
				{
					// new room
					reading = true;
					multiCount = 0;
				}

				if (reading && read.compare("END") == 0)
				{
					// end room
					reading = false;
					// check if room was multi
					if (temp.getType().compare("multi") == 0)
					{
						// add multi room to scene
						if (!scenes.at(i).addMultiRoom(temp, multiCount))
						{
							cout << "Error adding multi room to scene. " << scenes.at(i).getRoomFilename() << endl;
						}
						// add room to the scene's room list
					}
					else if (!scenes.at(i).addRoom(temp))
					{
						// room wasn't added
						cout << "Error adding room to scene. " << scenes.at(i).getRoomFilename() << endl;
						file.close();
						return false;
					}

					temp = Room();
				}

				if (reading)
				{
					// currently reading in room data
					// check for room name
					if(read.substr(0,read.find_first_of("|")).compare("ID") == 0)
					{
						// matches, set name
						temp.setName(read.substr(read.find_first_of("|") + 1));
					}
					else if (read.substr(0, read.find_first_of("|")).compare("DESC") == 0)
					{
						// room desc found, set it
						temp.setDescr(read.substr(read.find_first_of("|") + 1));
					}
					else if (read.substr(0, read.find_first_of("|")).compare("ITEM") == 0)
					{
						// trying to add item to room
						// check if item exists
						if (findItem(read.substr(read.find_first_of("|") + 1)))
						{
                            tempItem = getItem(read.substr(read.find_first_of("|") + 1));
							temp.addItem(&tempItem);
						}
						else
						{
							cout << scenes.at(i).getRoomFilename() << endl;
							// item does not exist
							cout << "Could not find item: " << read.substr(read.find_first_of("|") + 1) << endl;
						}
					}
					else if (read.substr(0, read.find_first_of("|")).compare("ENTITY") == 0)
					{
						// trying to add entity to room
						// check if entity exists
						if (findEntity(read.substr(read.find_first_of("|") + 1)))
						{
                            tempEnt = getEntity(read.substr(read.find_first_of("|") + 1));
							temp.addEntity(&tempEnt);
						}
						else
						{
							cout << scenes.at(i).getRoomFilename() << endl;
							// entity does not exist
							cout << "Could not find entity: " << read.substr(read.find_first_of("|") + 1) << endl;
						}
					}
					else if (read.substr(0, read.find_first_of("|")).compare("PATH") == 0)
					{
						// build path
						tempStr = read.substr(read.find_first_of("|") + 1); // everything after "PATH|" in line
						tempPath.setName(tempStr.substr(0, tempStr.find_first_of("|"))); // name of path
						tempStr = tempStr.substr(tempStr.find_first_of("|") + 1);	// everything after "<name>|" in line
						tempPath.setDesc(tempStr.substr(0, tempStr.find_first_of("|"))); // description of path
						tempStr = tempStr.substr(tempStr.find_first_of("|") + 1);	// everything after "<desc>|" in line
						tempPath.setDirection(tempStr); // direction of connection
						// try to add path
						if (!temp.addPath(tempPath))
						{
							cout << scenes.at(i).getRoomFilename() << endl;
							// path not added
							cout << "Did not add path " << tempPath.getName() << " to " << temp.getName() << endl;
						}

						tempPath.clear();
					}
					else if (read.substr(0, read.find_first_of("|")).compare("TYPE") == 0)
					{
						// room type found, set it
						if (!temp.setType(read.substr(read.find_first_of("|") + 1)))
						{
							cout << "Could not set room type." << endl;
							file.close();
							return false;
						}
						// check if multi, store count if so
						if (temp.getType().compare("multi") == 0)
						{
							read = read.substr(read.find_first_of("|") + 1);
							multiCount = atoi(read.substr(5).c_str());
						}
					}
				}
			}
			// close file
			file.close();
		}
		else
		{
			// file did not open
			cout << "Error opening rooms for scene.\n" << scenes.at(i).getRoomFilename() << endl;
			return false;
		}
	}

	// check that at least 2 rooms exist in each scene(start and end)
       for(size_t i = 0; i < scenes.size(); i++)
       {
		if(scenes.at(i).getNumRooms() < 2)
		{
			cout << "Not enough rooms for scene!" << endl;
			return false;
		}
       }

	return true;
}
/***********************************************************************************
Function: LoadEntities
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Reads entities from text file, adds to entities list
Arguments:	(O/P) bool - whether it loaded sucessfully
************************************************************************************/
bool Game::LoadEntities()
{
	string filename = "entity.txt";
	string read;
	bool reading = false;
	fstream file(filename, ios::in);
	vector<string> skills;
	string name;
	int health, stamina;

	if (file)
	{
		cout << "Loading entities." << endl;

		// file opened
		while (!file.eof())
		{
			// read file
			getline(file, read);

			// check for new line character on string
			if(read.length() > 2 && !isalnum(read.back()))
			{
				// the compiler is adding on the newline char to string!
				// pull it off!
				read = read.substr(0,read.length()-1);
			}

			// check for start/end entity
			if (!reading && read.compare("NEW") == 0)
			{
				// new entity start
				reading = true;
			}

			if (reading && read.compare("END") == 0)
			{
				// entity end
				reading = false;
				// add entity to list
				if (name.length() >= 1 && health >= 1 && stamina >= 0)
				{
					entities.push_back(Entity(name, health, stamina));
					// add skills to entity
					for (size_t i = 0; i < skills.size(); i++)
					{
						entities.back().addSkill(skills.at(i));
					}
				}
				else
				{
					// entity not added
					cout << "Entity not added." << endl;
				}

				skills.clear();
			}

			if (reading)
			{
				// currently reading entity data
				if (read.substr(0, read.find_first_of("|")).compare("NAME") == 0)
				{
					// adding name
					name = read.substr(read.find_first_of("|") + 1);
				}
				else if (read.substr(0, read.find_first_of("|")).compare("HEALTH") == 0)
				{
					// setting health
					health = atoi(read.substr(read.find_first_of("|") + 1).c_str());
				}
				else if (read.substr(0, read.find_first_of("|")).compare("STAMINA") == 0)
				{
					// setting stamina
					stamina = atoi(read.substr(read.find_first_of("|") + 1).c_str());
				}
				else if (read.substr(0, read.find_first_of("|")).compare("SKILL") == 0)
				{
					// add skill
					skills.push_back(read.substr(read.find_first_of("|") + 1));
				}
			}
		}

		file.close();
	}
	else
	{
		// file didn't open!
		cout << "Could not load entities." << endl;
		return false;
	}

	return true;
}
/***********************************************************************************
Function: LoadItems
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Reads items from text file, adds to items list
Arguments:	(O/P) bool - whether it loaded sucessfully
************************************************************************************/
bool Game::LoadItems()
{
	string filename = "items.txt";
	string read;
	bool reading = false;
	Item temp;
	fstream file(filename, ios::in);

	if (file)
	{

		cout << "Loading items. " << endl;

		// file opened
		while (!file.eof())
		{
			// read file
			getline(file, read);

			// check for new line character on string
			if(read.length() > 2 && !isalnum(read.back()))
			{
				// the compiler is adding on the newline char to string!
				// pull it off!
				read = read.substr(0,read.length()-1);
			}

			// check if start/end of item
			if (!reading && read.compare("NEW") == 0)
			{
				// new item start
				reading = true;
			}

			if (reading && read.compare("END") == 0)
			{
				// item end
				reading = false;
				// add item to list
				items.push_back(temp);
				temp.clear();
			}

			if (reading)
			{
				// currently reading entity data
				if (read.substr(0, read.find_first_of("|")).compare("FULLNAME") == 0)
				{
					// adding full name
					temp.setFullname(read.substr(read.find_first_of("|") + 1));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("NAME") == 0)
				{
					// adding name
					temp.setName(read.substr(read.find_first_of("|") + 1));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("DESC") == 0)
				{
					// adding item description
					temp.setDescr(read.substr(read.find_first_of("|") + 1));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("ROOM_DESC") == 0)
				{
					// adding item room description
					temp.setRoomDesc(read.substr(read.find_first_of("|") + 1));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("WEAPON") == 0)
				{
					// item is weapon, add weapon data
					temp.setType(3);
					temp.setVal(atoi(read.substr(read.find_first_of("|") + 1).c_str()));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("ARMOR") == 0)
				{
					// item is armor, add armor data
					temp.setType(4);
					temp.setVal(atoi(read.substr(read.find_first_of("|") + 1).c_str()));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("DRINK") == 0)
				{
					// item is drink, add drink data
					temp.setType(1);
					temp.setVal(atoi(read.substr(read.find_first_of("|") + 1).c_str()));
				}
				else if (read.substr(0, read.find_first_of("|")).compare("FOOD") == 0)
				{
					// item is food, add food data
					temp.setType(2);
					temp.setVal(atoi(read.substr(read.find_first_of("|") + 1).c_str()));
				}
			}
		}

		file.close();
	}
	else
	{
		// file did not open
		cout << "Could not load items." << endl;
		return false;
	}


	return true;
}
/***********************************************************************************
Function: findItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Checks items list for item by full name
Arguments:	(I/P) string itemName - full name of item
			(O/P) bool - found or not found
************************************************************************************/
bool Game::findItem(string itemName)
{
	bool found = false;
	size_t i;
	// for each item
	for (i = 0; i < items.size() && !found; i++)
	{
		// check if item exists
		found = (items.at(i).getFullname().compare(itemName) == 0);
	}

	return found;
}
/***********************************************************************************
Function: getItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns item with matching full name
Arguments:	(I/P) string itemName - full name of item
			(O/P) Item - corresponding item
************************************************************************************/
Item Game::getItem(string itemName)
{
	Item item;
	bool found = false;
	size_t i;

	// for each item
	for (i = 0; i < items.size() && !found; i++)
	{
		// check if item exists
		if (items.at(i).getFullname().compare(itemName) == 0)
		{
			found = true;
			item = items.at(i);
		}
	}

	return item;
}
/***********************************************************************************
Function: findEntity
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Checks entity list for entity by name
Arguments:	(I/P) string entityName - name of entity
			(O/P) bool - found or not found
************************************************************************************/
bool Game::findEntity(string entityName)
{
	bool found = false;
	size_t i;
	// for each entity
	for (i = 0; i < entities.size() && !found; i++)
	{
		// check if entity exists
		found = (entities.at(i).getName().compare(entityName) == 0);
	}

	return found;
}
/***********************************************************************************
Function: getEntity
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns entity with matching name
Arguments:	(I/P) string entityName - name of entity
			(O/P) Entity - corresponding entity
************************************************************************************/
Entity Game::getEntity(string entityName)
{
	Entity ent;
	bool found = false;
	size_t i;

	// for each entity
	for (i = 0; i < entities.size() && !found; i++)
	{
		// check if entity exists
		if (entities.at(i).getName().compare(entityName) == 0)
		{
			found = true;
			ent = entities.at(i);
		}
	}

	return ent;
}
/***********************************************************************************
Function: makeLower
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Converts a string to lowercase
Arguments:	(I/P) string str - original string
			(O/P) string - converted string
************************************************************************************/
string Game::makeLower(string str)
{
	string temp = "";
	for (size_t i = 0; i < str.length(); i++)
	{
		temp += tolower(str.at(i));
	}

	return temp;
}

/***********************************************************************************
Function: Play
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Executes game playing
Arguments:	(O/P) string filename - name of file
************************************************************************************/
void Game::Play(string filename)
{
	string read;
	bool quit = false;
	bool didCommand;

	while(!quit)
	{
		// display floor map
		currentScene->displayMap(player.getCurrentRoom());

		didCommand = false;

		read = "";

		while (read.length() < 1)
		{
			// get user decision
			getline(cin, read);
		}

		read = makeLower(read);

		if (player.getCurrentRoom()->getType().compare("end") == 0
			&& read.compare("yes") == 0)
		{
			// moving to next scene
			didCommand = true;
			currentScene = nextScene();
			player.moveScene(currentScene);

			// check if player wants to save
			cout << "Would you like to save? [y/n]" << endl;
			read = "";
			while (read.length() < 1)
			{
				getline(cin, read);
			}
			switch (read.at(0))
			{
			case 'Y':
			case 'y':
				cout << "Saving..." << endl;
				if (!SaveGame(filename))
				{
					cout << "Error while trying to save file..." << endl;
				}
				break;
			case 'N':
			case 'n':
			default:
				cout << endl << endl;
				break;
			}

			player.getCurrentRoom()->enter();
			// player moved, check for battle
			if (player.getCurrentRoom()->isFight())
			{
				// fight occurs
				battle();
				// room battle has been fought, update it
				player.getCurrentRoom()->battled();
				// check if player died
				if (player.isDead())
				{
					// player died!
					cout << "You have died!" << endl;
					cout << "GAME OVER" << endl << endl;
					return;
				}
			}
		}

		// check user input against commands
		for (size_t i = 0; i < commands.size() && !didCommand; i++)
		{
			// attempt to use each command until a command works
			didCommand = commands.at(i)->action(read, &player);
			if (didCommand && commands.at(i)->getCmdName().compare("move") == 0)
			{

				// player moved, check for battle
				if (player.getCurrentRoom()->isFight())
				{
					// fight occurs
					battle();
					// room battle has been fought, update it
					player.getCurrentRoom()->battled();
					// check if player died
					if (player.isDead())
					{
						// player died!
						cout << "You have died!" << endl;
						cout << "GAME OVER" << endl << endl;
						return;
					}
				}
			}
			else if (didCommand && commands.at(i)->getCmdName().compare("get") == 0)
			{
				// tell that item pickup was successful
				cout << "You picked up the " << commands.at(i)->removeCaller(read) << "." << endl;
			}
		}

		if (!didCommand)
		{
			// a command was not used
			// check for quit
			if (read.compare("quit") == 0)
			{
				quit = true;
			}
			else
			{
				cout << "Could not complete request." << endl;
				cout << "For command help, type 'help commands'." << endl;
				cout << "Or, type 'quit' to end game." << endl;
			}
		}

		if (player.getCurrentRoom()->getType().compare("end") == 0
			&& nextScene() != NULL)
		{
			// next scene exists and you are in end room for scene
			cout << endl << "Final room located." << endl;
			cout << "Move to next floor? [Enter yes to continue downwards]" << endl;
		}
		else if (player.getCurrentRoom()->getType().compare("end") == 0)
		{
			// final room of final scene
			cout << "You have reached the end of the game!" << endl;
			cout << "Congratulations!" << endl;
			cout << "YOU WIN!" << endl << endl;
			quit = true;
		}
	}
}
/***********************************************************************************
Function: IsLoaded
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns whether the game loaded correctly
Arguments:	(O/P) bool - whether game loaded correctly
************************************************************************************/
bool Game::IsLoaded()
{
	return loaded;
}
/***********************************************************************************
Function: NewGame
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Creates new game
Arguments:	(I/P) string playerName - name of player
************************************************************************************/
void Game::NewGame(string playerName)
{
	string filename = "player_" + playerName + ".txt";
	string read;
	bool classChosen = false;
	fstream file(filename, ios::out);

	if (file)
	{
		// file opened
		player.setName(playerName);
		while (!classChosen)
		{
			// get player class
			cout << "Choose a major: " << endl;
			cout << "a) CS" << endl
				<< "b) SE" << endl
				<< "c) CE" << endl
				<< "d) ATEC" << endl;

			read = "";
			while (read.size() < 1)
			{
				// get option
				getline(cin, read);
			}

			classChosen = true;
			switch (read.at(0))
			{
			case 'A':
			case 'a':
				// chose CS class
				player.setType(PlayerClasses::CS);
				break;
			case 'B':
			case 'b':
				// chose SE class
				player.setType(PlayerClasses::SE);
				break;
			case 'C':
			case 'c':
				// chose CE class
				player.setType(PlayerClasses::CE);
				break;
			case 'D':
			case 'd':
				// chose ATEC class
				player.setType(PlayerClasses::ATEC);
				break;
			default:
				// invalid selection
				cout << "Invalid selection." << endl;
				classChosen = false;
				break;
			}
		}

		// get first scene, load player into it
		currentScene = &scenes.at(0);
		for (size_t i = 0; i < scenes.size(); i++)
		{
			if (scenes.at(i).getOrder() < currentScene->getOrder())
			{
				currentScene = &scenes.at(i);
			}
		}
		player.moveScene(currentScene);
		// display room description
		player.getCurrentRoom()->enter();

		file.close();

		// save game
		if (!SaveGame(filename))
		{
			cout << endl << "Error, could not save game!" << endl;
		}

		Play(filename);
	}
	else
	{
		cout << "Error starting new game!" << endl;
	}
}
/***********************************************************************************
Function: Load
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Pushes commands to command list, calls other load functions
Arguments:	(O/P) bool - whether correctly loaded
************************************************************************************/
bool Game::Load()
{
	// add commands into list
	commands.push_back(&move_cmd);
	commands.push_back(&get_cmd);
	commands.push_back(&help_cmd);
	commands.push_back(&use_cmd);
	commands.push_back(&look_cmd);

	for (size_t i = 0; i < commands.size(); i++)
	{
		commands.at(i)->setCmdList(&commands);
	}

	// loads them in order
	return LoadScenes() && LoadEntities() && LoadItems() && LoadRooms();
}
/***********************************************************************************
Function: LoadGame
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Pushes commands to command list, calls other load functions
Arguments:	(I/P) string playerName - name of player
			(O/P) bool - whether correctly loaded
************************************************************************************/
bool Game::LoadGame(string playerName)
{
	Item temp;
	string read;
	int val;
	string filename = "player_" + playerName + ".txt";
	fstream file(filename, ios::in);

	if (file)
	{
		// file opened
		// load player data
		while (!file.eof())
		{
			// read file
			getline(file, read);

			// check for new line character on string
			if(read.length() > 2 && !isalnum(read.back()))
			{
				// the compiler is adding on the newline char to string!
				// pull it off!
				read = read.substr(0,read.length()-1);
			}

			if (read.substr(0, read.find_first_of("|")).compare("SCENE") == 0)
			{
				// load scene
				val = atoi(read.substr(read.find_first_of("|") + 1).c_str());
				for (size_t i = 0; i < scenes.size(); i++)
				{
					if (scenes.at(i).getOrder() == val)
					{
						currentScene = &scenes.at(i);
						player.moveScene(currentScene);
						// display room description
						player.getCurrentRoom()->enter();
					}
				}

				if (currentScene == NULL)
				{
					// scene not found
					cout << "Error loading player scene. " << endl;
					return false;
				}

			}
			else if (read.substr(0, read.find_first_of("|")).compare("ITEM") == 0)
			{
				// load an item
				read = read.substr(read.find_first_of("|") + 1);
				if (findItem(read))
				{
					// item exists, add to player
                                        temp = getItem(read);
					player.addItem(&temp);
				}
				else
				{
					cout << "Could not load player item: " << read << endl;
				}
			}
			else if (read.substr(0, read.find_first_of("|")).compare("LVL") == 0)
			{
				// load level and experience
				read = read.substr(read.find_first_of("|") + 1);
				val = atoi(read.substr(0, read.find_first_of("|")).c_str());	// level
				while (player.getLevel() < val)
				{
					player.addExp(player.getLevelUPExp());
				}
				read = read.substr(read.find_first_of("|") + 1);
				val = atoi(read.c_str());	// experience
				player.addExp(val);
			}
			else if (read.substr(0, read.find_first_of("|")).compare("HEALTH") == 0)
			{
				// load current health
				val = atoi(read.substr(read.find_first_of("|") + 1).c_str());
				while (player.getLife() < val)
				{
					player.restoreHealth(1);
				}
				while (player.getLife() > val)
				{
					player.restoreHealth(-1);
				}
			}
			else if (read.substr(0, read.find_first_of("|")).compare("CLASS") == 0)
			{
				 // check for type
				read = read.substr(read.find_first_of("|") + 1);
				if (read.compare("CS") == 0)
				{
					player.setType(PlayerClasses::CS);
				}
				else if (read.compare("CE") == 0)
				{
					player.setType(PlayerClasses::CE);
				}
				else if (read.compare("SE") == 0)
				{
					player.setType(PlayerClasses::SE);
				}
				else if (read.compare("ATEC") == 0)
				{
					player.setType(PlayerClasses::ATEC);
				}
				else
				{
					cout << "Error loading player class." << endl;
					file.close();
					return false;
				}
			}
		}
		file.close();

		cout << endl << "Weapon and armor will need to be re-equipped." << endl;

		Play(filename);

		return true;
	}
	else
	{
		return false;
	}

}
/***********************************************************************************
Function: SaveGame
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Saves player data to file
Arguments:	(I/P) string filename - name of player game file
			(O/P) bool - file loaded or not
************************************************************************************/
bool Game::SaveGame(string filename)
{
	fstream file(filename, ios::out);

	if (file)
	{
		// file opened
		// store player data
		// store current scene
		file << "SCENE|" << player.getCurrentScene()->getOrder() << endl;
		// store inventory
		file << "INVENTORY:" << endl;
		for (size_t i = 0; i < player.getInventory()->size(); i++)
		{
			if(player.getInventory()->at(i).isVisible())
				file << "ITEM|" << player.getInventory()->at(i).getFullname() << endl;
		}
		// store level and exp
		file << "LVL|" << player.getLevel() << "|" << player.getExp() << endl;
		// store current health
		file << "HEALTH|" << player.getLife() << endl;
		// store class
		file << "CLASS|" << player.getType() << endl;
		file.close();

		return true;
	}
	else
	{
		// error opening file
		return false;
	}
}
/***********************************************************************************
Function: nextScene
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns the next scene
Arguments:	(O/P) Scene * - next scene; null if last scene
************************************************************************************/
Scene * Game::nextScene()
{
	vector<int> temp;
	int nextScene;
	bool found = false;
	for (size_t i = 0; i < scenes.size(); i++)
	{
		temp.emplace_back(scenes.at(i).getOrder());
	}
	sort(temp.begin(), temp.end());

	for (size_t i = 0; i < temp.size() && !found; i++)
	{
		// find next highest value
		if (temp.at(i) > currentScene->getOrder())
		{
			nextScene = temp.at(i);
			found = true;
		}
	}

	if (found)
	{
		// next scene exists
		for (size_t i = 0; i < scenes.size(); i++)
		{
			// find matching scene and return it
			if (scenes.at(i).getOrder() == nextScene)
			{
				return &scenes.at(i);
			}
		}
	}
	else
	{
		// this is last scene
		return NULL;
	}
}
/***********************************************************************************
Function: battle
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Executes battle sequence
Arguments:	none
************************************************************************************/
void Game::battle()
{
	string read;
	int skillChoice, targetChoice, numLivingEnemies;
	int damageDealt;
	bool enemyLives = true;
	bool gotSkill, gotTarget;
	bool inputCheck;
	bool attacked;

	cout << "You have stumbled upon some enemies!" << endl;

	while (!player.isDead() && enemyLives)
	{
		// assume all enemies die this turn (will check at end of loop)
		enemyLives = false;
		// reset other flags
		gotSkill = false;
		gotTarget = false;
		attacked = false;
		numLivingEnemies = 0;

		// display battle scene
		for (size_t i = 0; i < player.getCurrentRoom()->getEntityList()->size(); i++)
		{
			if (!player.getCurrentRoom()->getEntityList()->at(i).isDead())
			{
				cout << numLivingEnemies+1 << ") " << player.getCurrentRoom()->getEntityList()->at(i).getName() <<
					": " << endl << 
					"Health: " << player.getCurrentRoom()->getEntityList()->at(i).getLife() << endl;
				numLivingEnemies++;
			}
		}
		cout << endl << "Player: " << endl;
		cout << "Health: " << player.getLife() << " | Stamina: " << player.getStamina() << endl;
		// give player attack options
		for (size_t i = 0; i < player.getSkillList()->size(); i++)
		{
			cout << i+1 << ") " << player.getSkillList()->at(i).getName() << " Cost: " 
				<< player.getSkillList()->at(i).getCost() << endl;
		}
		// get option and attack
		while (!attacked)
		{
			while (!gotSkill)
			{
				cout << "Enter skill option: " << endl;

				read = "";
				while (read.length() < 1)
				{
					getline(cin, read);
				}

				inputCheck = true;
				for (size_t i = 0; i < read.length() && inputCheck; i++)
				{
					if (!isdigit(read.at(i)))
					{
						// input not digit
						inputCheck = false;
					}
				}
				if (inputCheck)
				{
					// input was integer, check bounds
					skillChoice = atoi(read.c_str());
					if (skillChoice > 0 && skillChoice <= player.getSkillList()->size())
					{
						// within bounds
						gotSkill = true;
					}
				}
			}

			// check player stamina vs requirement
			if (player.getStamina() < player.getSkillList()->at(skillChoice-1).getCost())
			{
				// player does not have enough stamina
				cout << "You do not have enough stamina for this move!" << endl;
				gotSkill = false;
			}
			else
			{
				// choose attack target
				while (!gotTarget)
				{
					cout << "Enter target option: " << endl;

					read = "";
					while (read.length() < 1)
					{
						getline(cin, read);
					}

					inputCheck = true;
					for (size_t i = 0; i < read.length() && inputCheck; i++)
					{
						if (!isdigit(read.at(i)))
						{
							// input not digit
							inputCheck = false;
						}
					}
					if (inputCheck)
					{
						// input was integer, check bounds
						targetChoice = atoi(read.c_str());
						if (targetChoice > 0 && targetChoice <= numLivingEnemies)
						{
							// within bounds
							gotTarget = true;
						}
					}
				}

				for (size_t i = 0, j = 0; i < player.getCurrentRoom()->getEntityList()->size() && !attacked; i++)
				{
					if (!player.getCurrentRoom()->getEntityList()->at(i).isDead())
					{
						j++;
						if (j == targetChoice)
						{
							damageDealt = player.attack(&player.getSkillList()->at(skillChoice - 1));
							// enemy found, deal them damage
							player.getCurrentRoom()->getEntityList()->at(i).hurt(damageDealt);
							// check if enemy died
							if (player.getCurrentRoom()->getEntityList()->at(i).isDead())
							{
								cout << "You killed " << player.getCurrentRoom()->getEntityList()->at(i).getName() << endl;
							}
							else
							{
								cout << "You dealt " << damageDealt << " damage." << endl;
							}
							attacked = true;
						}
					}
				}

			}
		}
		// for each enemy that is alive
		for (size_t i = 0; i < player.getCurrentRoom()->getEntityList()->size() && !player.isDead(); i++)
		{
			if (!player.getCurrentRoom()->getEntityList()->at(i).isDead())
			{
				// enemy is living, let them attack
				damageDealt = player.getCurrentRoom()->getEntityList()->at(i).attack();
				cout << player.getCurrentRoom()->getEntityList()->at(i).getName() << " dealt " << damageDealt << " damage." << endl;
				player.hurt(damageDealt);
			}
		}

		// check if any entities still live
		for (size_t i = 0; i < player.getCurrentRoom()->getEntityList()->size() && !enemyLives; i++)
		{
			// if an entity is not yet dead, it will stop checking
			enemyLives = !player.getCurrentRoom()->getEntityList()->at(i).isDead();
		}
	}

	if (!player.isDead())
	{
		// if player is not dead, 
		// give experience based on number of dead enemies * 25
		player.addExp(player.getCurrentRoom()->getEntityList()->size() * 25);
		// re-display the room
		player.getCurrentRoom()->enter();
	}

}
