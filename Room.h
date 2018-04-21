/***********************************************************************************
File Name: Room.h
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
#pragma once

#include "Item.h"
#include "Pathway.h"
#include "Entity.h"

#include <string>
#include <vector>

using namespace std;

class Room
{
private:
	string name;	// name of room
	string description; // description for room itself
	string type;		// type of room (randomizable, start, end, normal)
	vector<Item> items; // list of items in room
	vector<Entity> entities;
	vector<Pathway> paths; // list of pathways from room to other rooms (north|south|etc...)
	bool visited, fought;
public:
	Room();
	~Room();
	string getName();
	string getType();
	void setName(string name);
	void setDescr(string desc);
	bool setType(string type);
	void addItem(Item* item);
	void addEntity(Entity* ent);
	void clear();
	bool addPath(Pathway path);
	vector<Item>* getItemList();
	vector<Pathway>* getPaths();
	vector<Entity>* getEntityList();
	void enter();
	bool isVisited();
	bool isFight();
	void battled();
};
