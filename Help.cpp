/***********************************************************************************
File Name: Help.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Help - displays command descriptions
Procedures:	Help() - constructor
			~Help() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Help Command
************************************************************************************/

#include <iostream>

#include "Help.h"

using namespace std;

/***********************************************************************************
Function: Help
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Help::Help()
{
	
	// add default callers/receivers for help command
	// default callers for help
	addCmdName("help");
	addCmdName("?");
	// default receiver for help
	addReceiver("commands");

	setName("help");
	setDesc("'help <command>|commands' ---- used to get command assistance");
}

/***********************************************************************************
Function: ~Help
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Help::~Help()
{
}

/***********************************************************************************
Function: action
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempts to use the Help command
Arguments:	(I/P):
				string cmd - command that is being parsed
				Player* player - pointer to player object
			(O/P) bool - if command was successful
************************************************************************************/
bool Help::action(string cmd, Player* player)
{
	string temp;
	bool found = false;

	resetReceivers();
	addReceiver("commands");
	// add all command names
	for (size_t i = 0; i < cmdListPtr->size(); i++)
	{
		addReceiver(cmdListPtr->at(i)->getCmdName());
	}

	if (checkCommand(cmd))
	{
		// command is valid
		temp = removeCaller(cmd);

		if (temp.compare("commands") == 0)
		{
			found = true;
			// display every command help
			for (size_t i = 0; i < cmdListPtr->size(); i++)
			{
				cout << cmdListPtr->at(i)->getCmdDesc() << endl;
			}
		}
		else
		{
			// for each command, check if matches temp
			for (size_t i = 0; i < cmdListPtr->size() && !found; i++)
			{
				if (cmdListPtr->at(i)->checkName(temp))
				{
					// names match
					// display this command
					cout << cmdListPtr->at(i)->getCmdDesc() << endl;
					found = true;
				}
			}
		}


	}
	return found;
}
