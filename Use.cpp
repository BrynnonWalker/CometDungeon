/***********************************************************************************
File Name: Use.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Use - displays information corresponding to command
Procedures:	Use() - constructor
			~Use() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Use Command
************************************************************************************/
#include "Use.h"

#include <iostream>

using namespace std;

/***********************************************************************************
Function: Use
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Use::Use()
{
	setSplit(true);
	// add default callers/receivers for use command
	// default callers for help
	addCmdName("use");
	addCmdName("");

	setName("use");
	setDesc("'use <item>' ---- use an item from inventory");
}

/***********************************************************************************
Function: ~Use
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Use::~Use()
{
}

/***********************************************************************************
Function: action
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempts to use the Use command
Arguments:	(I/P):
				string cmd - command that is being parsed
				Player* player - pointer to player object
			(O/P) bool - if command was successful
************************************************************************************/
bool Use::action(string cmd, Player * player)
{
	vector<Item*> itemList;
	string temp;
	string::size_type tempLoc;
	bool found = false;
	bool inputCheck = false;
	int choice;
	bool gotChoice = false;

	// reset receivers
	resetReceivers();
	// get list of items in inventory
	for (size_t i = 0; i < player->getInventory()->size(); i++)
	{
		// add name and full name to receiver list
		addReceiver(player->getInventory()->at(i).getName());
		addReceiver(player->getInventory()->at(i).getFullname());
	}

	// check cmd
	if (checkCommand(cmd))
	{
		// command is valid
		temp = removeCaller(cmd);
		// split temp into receiver tokens

		for (size_t i = 0; i < getSplitters()->size() && temp.size() > 0; i++)
		{
			tempLoc = temp.find(getSplitters()->at(i));
			if (tempLoc != string::npos)
			{
				// splitter found
				// check substr against items
				for (size_t j = 0; j < player->getInventory()->size() && temp.size() > 0; j++)
				{
					// if temp == item name || temp = item full name && item is visible
					if (player->getInventory()->at(j).isVisible() &&
						(player->getInventory()->at(j).getName().compare(temp.substr(0, tempLoc)) == 0
						|| player->getInventory()->at(j).getFullname().compare(temp.substr(0, tempLoc)) == 0))
					{
						// add to item list
						itemList.push_back(&player->getInventory()->at(i));
						// reduce temp
						temp = temp.substr(tempLoc + getSplitters()->at(i).length() + 2);
					}
				}
			}
		}

		// check item list one more time
		if (temp.size() > 0)
		{
			found = false;
			for (size_t i = 0; i < player->getInventory()->size(); i++)
			{
				// if temp == item name || temp == item full name && item is visible
				if (player->getInventory()->at(i).isVisible() && 
					(player->getInventory()->at(i).getName().compare(temp) == 0
					|| player->getInventory()->at(i).getFullname().compare(temp) == 0))
				{
					// add to item list
					itemList.push_back(&player->getInventory()->at(i));
				}
			}
		}

	}

	while (itemList.size() > 1 && !gotChoice)
	{
		// more than 1 item was found
		cout << "Multiple items found. Please choose: " << endl;
		for (size_t i = 0; i < itemList.size(); i++)
		{
			cout << i + 1 << ") " << itemList.at(i)->getFullname() << endl;
		}

		temp = "";
		while (temp.length() < 1)
		{
			getline(cin, temp);
		}

		inputCheck = true;
		for (size_t i = 0; i < temp.length() && inputCheck; i++)
		{
			if (!isdigit(temp.at(i)))
			{
				// input not digit
				inputCheck = false;
			}
		}
		if (inputCheck)
		{
			// input was integer, check bounds
			choice = atoi(temp.c_str());
			if (choice > 0 && choice <= itemList.size())
			{
				// within bounds
				gotChoice = true;
			}
		}
	}
	if (gotChoice)
	{
		// use player item
		found = false;
		for (size_t i = 0; i < player->getInventory()->size() && !found; i++)
		{
			// find item
			if (player->getInventory()->at(i).getFullname().compare(itemList.at(choice - 1)->getFullname()) == 0)
			{
				// item found
				if (player->getInventory()->at(i).canConsume())
				{
					// consumable
					if (player->getInventory()->at(i).consumeType())
					{
						// drink
						player->restoreStamina(player->getInventory()->at(i).consume());
					}
					else
					{
						// food
						player->restoreHealth(player->getInventory()->at(i).consume());
					}

					cout << "Item consumed." << endl;
				}
				else if (player->getInventory()->at(i).getType().compare("weapon") == 0 ||
					player->getInventory()->at(i).getType().compare("armor") == 0)
				{
					// weapon or armor
					player->equip(&player->getInventory()->at(i));
					cout << "Item equipped." << endl;
				}
				found = true;
			}
		}
	}
	else if (itemList.size() == 1)
	{
		// use player item
		found = false;
		for (size_t i = 0; i < player->getInventory()->size() && !found; i++)
		{
			// find item
			if (player->getInventory()->at(i).getFullname().compare(itemList.at(0)->getFullname()) == 0)
			{
				// item found
				if (player->getInventory()->at(i).canConsume())
				{
					// consumable
					if (player->getInventory()->at(i).consumeType())
					{
						// drink
						player->restoreStamina(player->getInventory()->at(i).consume());
					}
					else
					{
						// food
						player->restoreHealth(player->getInventory()->at(i).consume());
					}

					cout << "Item consumed." << endl;

				}
				else if (player->getInventory()->at(i).getType().compare("weapon") == 0 ||
					player->getInventory()->at(i).getType().compare("armor") == 0)
				{
					// weapon or armor
					player->equip(&player->getInventory()->at(i));
					cout << "Item equipped." << endl;
				}
				found = true;
			}
		}
	}

	return found;
}
