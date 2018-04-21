/***********************************************************************************
File Name: Get.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Get - command that attempts to add an object to player inventory
Procedures:	Get() - constructor
			~Get() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Get Command
************************************************************************************/

#include <iostream>

#include "Get.h"

using namespace std;

/***********************************************************************************
Function: Get
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Get::Get()
{
	setSplit(true);
	// add default callers/receivers for getting items
	// default callers for getting stuff
	addCmdName("get");
	addCmdName("take");
	addCmdName("collect");
	addCmdName("grab");

	// set name
	setName("get");
	// set description
	setDesc("'get <item>' ---- used to pick up items");
}

/***********************************************************************************
Function: ~Get
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Get::~Get()
{
}

/***********************************************************************************
Function: action
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempts to use the Get command
Arguments:	(I/P):
				string cmd - command that is being parsed
				Player* player - pointer to player object
			(O/P) bool - if command was successful
************************************************************************************/
bool Get::action(string cmd, Player* player)
{
	vector<Item*> itemList;
	string temp;
	string::size_type tempLoc;
	bool found = false;
	bool inputCheck = false;
	int choice;
	bool gotChoice = false;
	Room* ptr = player->getCurrentRoom();
	// reset receivers
	resetReceivers();
	// get list of items for the player room and add to receiver
	for (size_t i = 0; i < ptr->getItemList()->size(); i++)
	{
		// check if item is visible in room
		if (ptr->getItemList()->at(i).isVisible())
		{
			// item is visible, add to receivers
			addReceiver(ptr->getItemList()->at(i).getName());
			addReceiver(ptr->getItemList()->at(i).getFullname());
		}
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
				for (size_t j = 0; j < ptr->getItemList()->size() && temp.size() > 0; j++)
				{
					// if temp == item name || temp = item full name
					if (ptr->getItemList()->at(j).getName().compare(temp.substr(0, tempLoc)) == 0
						|| ptr->getItemList()->at(j).getFullname().compare(temp.substr(0, tempLoc)) == 0)
					{
						// put item into item list
						itemList.push_back(&ptr->getItemList()->at(j));
						// reduce temp
						temp = temp.substr(tempLoc + getSplitters()->at(i).length() + 2);
					}
				}
			}
		}

		// check item list one more time
		if (temp.size() > 0)
		{
			for (size_t i = 0; i < ptr->getItemList()->size(); i++)
			{
				// if temp == item name || temp == item full name
				if (ptr->getItemList()->at(i).getName().compare(temp) == 0
					|| ptr->getItemList()->at(i).getFullname().compare(temp) == 0)
				{
					// put item into item list
					itemList.push_back(&ptr->getItemList()->at(i));
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
		// give player item
		player->addItem(itemList.at(choice - 1));
		// make this item invisible in the room
		found = false;
		for (size_t i = 0; i < ptr->getItemList()->size() && !found; i++)
		{
			if (ptr->getItemList()->at(i).getFullname().compare(itemList.at(choice - 1)->getFullname()) == 0)
			{
				ptr->getItemList()->at(i).flipVisibility();
				found = true;
			}
		}
	}
	else if (itemList.size() == 1)
	{
		// give player item
		player->addItem(itemList.at(0));
		// make this item invisible in the room
		found = false;
		for (size_t i = 0; i < ptr->getItemList()->size() && !found; i++)
		{
			if (ptr->getItemList()->at(i).getFullname().compare(itemList.at(0)->getFullname()) == 0)
			{
				ptr->getItemList()->at(i).flipVisibility();
				found = true;
			}
		}
	}

	return found;
}
