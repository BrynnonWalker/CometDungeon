/***********************************************************************************
File Name: Room.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Room - object holding items, entities, and paths to neighboring rooms
Procedures:	Room() - default constructor
			~Room() - destructor
			string getName() - returns room name
			string getType() - returns room type
			void setName(string name) - sets room name
			void setDescr(string desc) - sets room description
			bool setType(string type) - sets room type
			void addItem(Item* item) - adds item to room
			void addEntity(Entity* ent) - adds entity to room
			void clear() - resets room to default values
			bool addPath(Pathway path) - adds path to room
			vector<Item>* getItemList() - returns list of items in room
			vector<Pathway>* getPaths() - returns list of paths from room
			vector<Entity>* getEntityList() - returns list of entities in room
			void enter() - enters room and displays room info
			bool isVisited() - checks whether room has been visited
			bool isFight() - checks whether a battle has already been fought in room
			void battled() - sets that room has been fought in
************************************************************************************/

#include <iostream>

#include "Room.h"

using namespace std;

/***********************************************************************************
Function: Room
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor; sets to default values
Arguments:	none
************************************************************************************/
Room::Room()
{
	clear();
}

/***********************************************************************************
Function: ~Room
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Room::~Room()
{
}

/***********************************************************************************
Function: getName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns name of room
Arguments:	(O/P) string - name of room
************************************************************************************/
string Room::getName()
{
	return name;
}

/***********************************************************************************
Function: getType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns type of room
Arguments:	(O/P) string - type of room
************************************************************************************/
string Room::getType()
{
	return type;
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets name of room to input string
Arguments:	(I/P) string name - name of room
************************************************************************************/
void Room::setName(string name)
{
	this->name = name;
}

/***********************************************************************************
Function: setDescr
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets description of room
Arguments:	(I/P) string - description of room
************************************************************************************/
void Room::setDescr(string desc)
{
	description = desc;
}

/***********************************************************************************
Function: setType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the type of room
Arguments:	(I/P) string type - type of room
			(O/P) bool - checks if room type set correctly
************************************************************************************/
bool Room::setType(string type)
{
	// check type against possible types
	if (type.compare("start") == 0 || type.compare("end") == 0
		|| type.compare("single") == 0)
	{
		// matches one of the possible types, add it
		this->type = type;
		return true;
	}
	// check multi type
	if (type.substr(0, 5).compare("multi") == 0)
	{
		this->type = type.substr(0, 5);
		return true;
	}
	return false;
}

/***********************************************************************************
Function: addItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds an item to the list of items in room
Arguments:	(I/P) Item * item - item to be added
************************************************************************************/
void Room::addItem(Item* item)
{
	items.emplace_back(*item);
}

/***********************************************************************************
Function: addEntity
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds an entity to the list of entities in room
Arguments:	(I/P) Entity * ent - entity to be added
************************************************************************************/
void Room::addEntity(Entity * ent)
{
	entities.emplace_back(*ent);
}

/***********************************************************************************
Function: addPath
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds path to the list of paths from room
Arguments:	(I/P) Pathway path - path to be added
			(O/P) bool - whether path was added
************************************************************************************/
bool Room::addPath(Pathway path)
{
	bool exists = false;
	// check if path direction already exists
	for (size_t i = 0; i < paths.size() && !exists; i++)
	{
		// for each path in room, check direction
		if (paths.at(i).getDirection().compare(path.getDirection()) == 0)
		{
			// both paths point to same direction
			exists = true;
		}
	}

	if (!exists)
	{
		// path direction not in use
		// add it
		paths.push_back(path);
	}

	return !exists;
}

/***********************************************************************************
Function: getItemList
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns list of items in the room
Arguments:	(O/P) vector<Item>* - list of items
************************************************************************************/
vector<Item>* Room::getItemList()
{
	return &items;
}

/***********************************************************************************
Function: clear
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: resets room values to default values
Arguments:	none
************************************************************************************/
void Room::clear()
{
	name = "";
	description = "";
	items.clear();
	paths.clear();
	visited = false;
	fought = false;
}

/***********************************************************************************
Function: getPaths
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns a list of paths from room
Arguments:	(O/P) vector<Pathway>* - list of paths from room
************************************************************************************/
vector<Pathway>* Room::getPaths()
{
	return &paths;
}

/***********************************************************************************
Function: getEntityList
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns a list of entities in room
Arguments:	(O/P) vector<Entity>* - list of entities in room
************************************************************************************/
vector<Entity>* Room::getEntityList()
{
	return &entities;
}

/***********************************************************************************
Function: enter
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: enters room and displays room info
Arguments:	none
************************************************************************************/
void Room::enter()
{
	visited = true;

	// display room description
	cout << endl;
	cout << description << endl;

	// display paths
	for (size_t i = 0; i < paths.size(); i++)
	{
		if (paths.at(i).isConnected())
		{
			// path exists, display it
			paths.at(i).display();

		}
	}

	// display visible items
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items.at(i).isVisible())
		{
			// item can be seen
			items.at(i).display();
		}
	}
}

/***********************************************************************************
Function: isVisited
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks whether room has been visited
Arguments:	(O/P) bool - whether room has been visited
************************************************************************************/
bool Room::isVisited()
{
	return visited;
}

/***********************************************************************************
Function: isFight
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks whether fight has occurred in room
Arguments:	(O/P) bool - whether fight has occurred
************************************************************************************/
bool Room::isFight()
{
	return entities.size() > 0 && !fought;
}

/***********************************************************************************
Function: addItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets room has been fought in
Arguments:	none
************************************************************************************/
void Room::battled()
{
	fought = true;
}
