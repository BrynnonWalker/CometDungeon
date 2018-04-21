/***********************************************************************************
File Name: Look.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Look - displays information corresponding to command
Procedures:	Look() - constructor
			~Look() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Look Command
************************************************************************************/

#include <iostream>

#include "Look.h"

using namespace std;

/***********************************************************************************
Function: Look
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Look::Look()
{
	// add default callers/receivers for getting items
	// default callers for getting stuff
	addCmdName("look");
	addCmdName("examine");
	addCmdName("see");
	addCmdName("view");

	// set name
	setName("look");
	// set description
	setDesc("'examine room|inventory|<item>' ---- look at details of items");
}

/***********************************************************************************
Function: ~Look
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Look::~Look()
{
}

/***********************************************************************************
Function: action
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempts to use the Look command
Arguments:	(I/P):
				string cmd - command that is being parsed
				Player* player - pointer to player object
			(O/P) bool - if command was successful
************************************************************************************/
bool Look::action(string cmd, Player * player)
{
	string temp;
	bool found = false;

	// reset receivers
	resetReceivers();

	addReceiver("room");
	addReceiver("inventory");

	// get list of items for the player room and add to receiver
	for (size_t i = 0; i < player->getCurrentRoom()->getItemList()->size(); i++)
	{
		// check if item is visible in room
		if (player->getCurrentRoom()->getItemList()->at(i).isVisible())
		{
			// item is visible, add to receivers
			addReceiver(player->getCurrentRoom()->getItemList()->at(i).getName());
			addReceiver(player->getCurrentRoom()->getItemList()->at(i).getFullname());
		}
	}
	// get list of items in inventory
	for (size_t i = 0; i < player->getInventory()->size(); i++)
	{
		// make sure they are visible
		if (player->getInventory()->at(i).isVisible())
		{
			addReceiver(player->getInventory()->at(i).getName());
			addReceiver(player->getInventory()->at(i).getFullname());
		}
	}

	if (checkCommand(cmd))
	{
		// command is valid
		temp = removeCaller(cmd);

		if (temp.compare("room") == 0)
		{
			found = true;
			// display room
			player->getCurrentRoom()->enter();
		}
		else if (temp.compare("inventory") == 0)
		{
			found = true;
			// display list of inventory items
			cout << "You view your inventory: " << endl;
			for (size_t i = 0; i < player->getInventory()->size(); i++)
			{
				cout << player->getInventory()->at(i).getName() << endl;
			}
		}
		else
		{
			// look for item to display description
			// check room
			for (size_t i = 0; i < player->getCurrentRoom()->getItemList()->size(); i++)
			{
				// check temp against item names and if the room item is visible
				if (player->getCurrentRoom()->getItemList()->at(i).isVisible() &&
					(player->getCurrentRoom()->getItemList()->at(i).getName().compare(temp) == 0
					|| player->getCurrentRoom()->getItemList()->at(i).getFullname().compare(temp) == 0))
				{
					// item found
					found = true;
					player->getCurrentRoom()->getItemList()->at(i).displayInfo();
				}
			}
			// check inventory
			for (size_t i = 0; i < player->getInventory()->size(); i++)
			{
				// check temp against item names and if the item is visible
				if (player->getInventory()->at(i).isVisible() &&
					(player->getInventory()->at(i).getName().compare(temp) == 0
					|| player->getInventory()->at(i).getFullname().compare(temp) == 0))
				{
					// item found
					found = true;
					player->getInventory()->at(i).displayInfo();
				}
			}
		}
	}

	return found;
}
