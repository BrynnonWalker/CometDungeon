/***********************************************************************************
File Name: Item.cpp
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

#include <iostream>

#include "Item.h"

using namespace std;

/***********************************************************************************
Function: Items
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Item::Item()
{
	clear();
}

/***********************************************************************************
Function: Items
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Item::~Item()
{
}

/***********************************************************************************
Function: clear
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: resets to default values
Arguments:	none
************************************************************************************/
void Item::clear()
{
	fullname = "";
	name = "default name";
	roomDesc = "default room desc";
	description = "";
	modifier = 0;
	visible = true;
	consumed = true;
	equipment = consumable = drink = food = weapon = armor = false;
	misc = true;
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the item name
Arguments:	(I/P) string name - the item's name
************************************************************************************/
void Item::setName(string name)
{
	this->name = name;
}

/***********************************************************************************
Function: getName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets the item name
Arguments:	(O/P) string - the item's name
************************************************************************************/
string Item::getName()
{
	return name;
}

/***********************************************************************************
Function: getFullName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets the item full name
Arguments:	(O/P) string - the item's full name
************************************************************************************/
string Item::getFullname()
{
	return fullname;
}

/***********************************************************************************
Function: getDesc
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets the item description
Arguments:	(O/P) string - the item's description
************************************************************************************/
string Item::getDesc()
{
	return description;
}

/***********************************************************************************
Function: setFullName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the item full name
Arguments:	(I/P) string name - the item's full name
************************************************************************************/
void Item::setFullname(string name)
{
	fullname = name;
}

/***********************************************************************************
Function: setFullDesc
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the item full name
Arguments:	(I/P) string name - the item's full name
************************************************************************************/
void Item::setDescr(string descr)
{
	description = descr;
}
/***********************************************************************************
Function: setRoomDesc
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the room description
Arguments:	(I/P) string desc - the room's description
************************************************************************************/
void Item::setRoomDesc(string desc)
{
	roomDesc = desc;
}

/***********************************************************************************
Function: setVal
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the modifier value
Arguments:	(I/P) int mod - the new modifier value
************************************************************************************/
void Item::setVal(int mod)
{
	modifier = mod;
}

/***********************************************************************************
Function: isVisible
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if item is visible
Arguments:	(O/P) bool - returns if item is visible
************************************************************************************/
bool Item::isVisible()
{
	return visible;
}

/***********************************************************************************
Function: flipVisibility
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: changes item visibility
Arguments:	none
************************************************************************************/
void Item::flipVisibility()
{
	visible = !visible;
}

/***********************************************************************************
Function: canEquip
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if item can be equipped
Arguments:	(O/P) bool - if item can be equipped
************************************************************************************/
bool Item::canEquip()
{
	return equipment;
}

/***********************************************************************************
Function: canConsume
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if item can be consumed
Arguments:	(O/P) bool - if item can be consumed
************************************************************************************/
bool Item::canConsume()
{
	return consumable;
}
/***********************************************************************************
Function: consumeType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if item is a drink or food
Arguments:	(O/P) bool - true if item is drink, false if food
************************************************************************************/
bool Item::consumeType()
{
	return drink;
}
/***********************************************************************************
Function: display
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: displays room description
Arguments:	none
************************************************************************************/
void Item::display()
{
	cout << roomDesc << endl;
}
/***********************************************************************************
Function: displayInfo
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: displays item description
Arguments:	none
************************************************************************************/
void Item::displayInfo()
{
	cout << description << endl;
}
/***********************************************************************************
Function: consume
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempts to consume the item
Arguments:	(O/P) int - returns the modifier; or 0
************************************************************************************/
int Item::consume()
{
	if (!consumable || consumed)
	{
		return 0;
	}
	else
	{
		visible = false;
		consumed = true;
		return modifier;
	}
}
/***********************************************************************************
Function: getMod
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets modifier
Arguments:	(O/P) int - the modifier
************************************************************************************/
int Item::getMod()
{
	return modifier;
}
/***********************************************************************************
Function: setType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the item type
Arguments:	(I/P) int type - type of item
************************************************************************************/
void Item::setType(int type)
{
	switch (type)
	{
	case 1:
		// drink
		consumed = false;
		consumable = true;
		drink = true;
		break;
	case 2:
		// food
		consumed = false;
		consumable = true;
		food = true;
		break;
	case 3:
		// weapon
		equipment = true;
		weapon = true;
		break;
	case 4:
		// armor
		equipment = true;
		armor = true;
		break;
	default:
		// misc
		misc = true;
		break;
	}
}

/***********************************************************************************
Function: getType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets item type
Arguments:	(O/P) string - type of item
************************************************************************************/
string Item::getType()
{
	string type;
	if (drink || food)
	{
		type = "consumable";
	}
	else if (weapon)
	{
		type = "weapon";
	}
	else if (armor)
	{
		type = "armor";
	}
	else
	{
		type = "unknown";
	}

	return type;
}
