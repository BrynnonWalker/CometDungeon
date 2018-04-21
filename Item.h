/***********************************************************************************
File Name: Item.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Item - stores item data
Procedures:	Item() - constructor
			~Item() - destructor
			void clear() - resets to default values
			void setName(string name) - sets name of item
			string getName() - gets name of item
			string getFullname() - gets the full name of item
			string getDesc() - gets description of item
			void setFullname(string name) - sets full name of item
			void setDescr(string descr) - sets description of item
			void setRoomDesc(string desc) - sets room description
			void setVal(int mod) - sets items modifier
			bool isVisible() - checks if item is visible
			void flipVisibility() - flips visibility of item
			bool canEquip() - if it can be equipped or not
			bool canConsume() - if it can be consumed or not
			bool consumeType() - returns if item is drink or food
			void display() - displays room description
			void displayInfo() - displays item description
			int consume() - consumes the item
			int getMod() - gets the item modifier
			void setType(int type) - sets the item type
			string getType() - gets the item type
************************************************************************************/


#pragma once

#include <string>

using namespace std;


class Item
{
private:
	string fullname, name;	
	string roomDesc, description;
	int modifier;			
	bool visible;
	bool consumed;
	bool equipment, consumable;
	bool drink, food, weapon, armor, misc;
public:
	Item();
	~Item();
	void clear();
	void setName(string name);
	string getName();
	string getFullname();
	string getDesc();
	void setFullname(string name);
	void setDescr(string descr);
	void setRoomDesc(string desc);
	void setVal(int mod);
	bool isVisible();
	void flipVisibility();
	bool canEquip();			// if it can be equipped or not
	bool canConsume();			// if it can be consumed or not (ex: potions, water bottle, bread)
	bool consumeType();
	void display();
	void displayInfo();
	int consume();
	int getMod();
	void setType(int type);
	string getType();
};

