/***********************************************************************************
File Name: Command.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Command - base object for all commands
Procedures: void setName(string name) - sets the command name
			void setDesc(string desc) - sets the command description
			void setCmdList(vector<Command*>* cmdList) - sets the command list
			Command() - constructs a command
			~Command() - destructs a command
			void clear() - resets command data
			void resetCallers() - clears the caller list
			void resetReceivers() - clears the receiver list
			void setSplit(bool flag) - sets whether command can have multiple receivers
			bool checkName(string name) - checks if command name matches input
			bool addCmdName(string caller) - add new caller for command
			bool addReceiver(string receiver) - add new receiver for command
			bool checkCommand(string cmd) - checks cmd for appropriate callers and receivers
			string removeCaller(string cmd) - returns the input - caller
			string getCmdName() - returns command name
			string getCmdDesc() - returns command description
			vector<string>* getSplitters() - returns a pointer to splitters vector
			virtual bool action(string cmd, Player* player) = 0 - virtual form of action function (implemented in child classes)
************************************************************************************/

#include "Command.h"

/***********************************************************************************
Function: Command
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Constructs default command object
Arguments:	none
************************************************************************************/
Command::Command()
{
	name = "default command name";
	description = "Command description";
	clear();
}

/***********************************************************************************
Function: ~Command
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Destructs command object
Arguments:	none
************************************************************************************/
Command::~Command()
{
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Sets command name
Arguments:	(I/P) string name - name of command
************************************************************************************/
void Command::setName(string name)
{
	this->name = name;
}
/***********************************************************************************
Function: setDesc
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Sets command description
Arguments:	(I/P) string desc - description of command
************************************************************************************/
void Command::setDesc(string desc)
{
	description = desc;
}
/***********************************************************************************
Function: setCmdList
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Sets command list
Arguments:	(I/P) vector<Command *> - a vector containing commands
************************************************************************************/
void Command::setCmdList(vector<Command*>* cmdList)
{
	cmdListPtr = cmdList;
}

/***********************************************************************************
Function: clear
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Clears command data
Arguments:	none
************************************************************************************/
void Command::clear()
{
	callers.clear();
	receivers.clear();
	allowSplit = false;
}
/***********************************************************************************
Function: resetCallers
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Clears callers
Arguments:	none
************************************************************************************/
void Command::resetCallers()
{
	callers.clear();
}
/***********************************************************************************
Function: resetReceivers
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Clears receivers
Arguments:	none
************************************************************************************/
void Command::resetReceivers()
{
	receivers.clear();
}
/***********************************************************************************
Function: setSplit
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets whether or not a command can have multiple receivers
Arguments:	(I/P) bool flag - whether or not a command can have multiple receivers
************************************************************************************/
void Command::setSplit(bool flag)
{
	allowSplit = flag;
}
/***********************************************************************************
Function: checkName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if the command name matches input
Arguments:	(I/P) string name - input command name
			(O/P) bool - whether the command name matches input
************************************************************************************/
bool Command::checkName(string name)
{
	return this->name.compare(name) == 0;
}
/***********************************************************************************
Function: removeCaller
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Removes the caller from the input string
Arguments:	(I/P) string cmd - input string
			(O/P) string - input string minus the caller; empty if caller not found
************************************************************************************/
string Command::removeCaller(string cmd)
{
	for (size_t i = 0; i < callers.size(); i++)
	{
		if (cmd.length() > callers.at(i).length() &&
			cmd.substr(0, callers.at(i).length()).compare(callers.at(i)) == 0)
		{
			// cmd caller found
			return cmd.substr(callers.at(i).length()+1);
		}
	}

	// not found, return empty string
	return "";
}
/***********************************************************************************
Function: getCmdName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns command name
Arguments:	(O/P) string - command name
************************************************************************************/
string Command::getCmdName()
{
	return name;
}
/***********************************************************************************
Function: getCmdDesc
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns command description
Arguments:	(O/P) string - command description
************************************************************************************/
string Command::getCmdDesc()
{
	return name + "|" + description;
}
/***********************************************************************************
Function: getSplitters
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Returns a pointer to splitters vector
Arguments:	(O/P) vector<string>* - a pointer to splitters vector
************************************************************************************/
vector<string>* Command::getSplitters()
{
	return &splitters;
}
/***********************************************************************************
Function: addCmdName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Add new caller for command
Arguments:	(I/P) string caller - command to be added
			(O/P) bool - whether command was added or not
************************************************************************************/
bool Command::addCmdName(string caller)
{
	bool found = false;
	// check if already added
	for (size_t i = 0; i < callers.size() && !found; i++)
	{
		if (callers.at(i).compare(caller) == 0)
		{
			// cmd name already exists in list
			found = true;
		}
	}

	if (!found)
	{
		// cmd name doesn't exist yet
		// add it
		callers.push_back(caller);
	}

	// return true if wasn't already in list
	return !found;
}
/***********************************************************************************
Function: addReceiver
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Add new receiver for command
Arguments:	(I/P) string receiver - receiver to be added
			(O/P) bool - whether receiver was added or not
************************************************************************************/
bool Command::addReceiver(string receiver)
{
	bool found = false;
	// check if already added
	for (size_t i = 0; i < receivers.size() && !found; i++)
	{
		if (receivers.at(i).compare(receiver) == 0)
		{
			// parameter already exists in list
			found = true;
		}
	}

	if (!found)
	{
		// parameter doesn't exist yet
		// add it
		receivers.push_back(receiver);
	}

	// return true if wasn't already in list
	return !found;
}
/***********************************************************************************
Function: checkCommand
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Checks cmd for appropriate callers and receivers
Arguments:	(I/P) string cmd - command line to be checked
			(O/P) bool - whether command and receivers were valid or not
************************************************************************************/
bool Command::checkCommand(string cmd)
{
	string temp;
	string::size_type tempLoc;
	bool foundCaller = false;
	bool foundReceiver = false;
	// check first part of cmd for caller
	for (size_t i = 0; i < callers.size() && !foundCaller; i++)
	{
		// if caller == start of cmd
		if (callers.at(i).compare(cmd.substr(0, callers.at(i).length())) == 0)
		{
			// caller found
			foundCaller = true;
			// store rest of cmd in temp
			temp = removeCaller(cmd);
		}
	}

	if (foundCaller && allowSplit && temp.size() > 0)
	{
		// split temp into receiver tokens

		for (size_t i = 0; i < splitters.size() && temp.size() > 0; i++)
		{
			tempLoc = temp.find(splitters.at(i));
			if (tempLoc != string::npos)
			{
				// splitter found
				// check substr against receivers
				foundReceiver = false;
				for (size_t j = 0; j < receivers.size() && temp.size() > 0 && !foundReceiver; j++)
				{
					// if temp == receiver
					if (receivers.at(j).compare(temp.substr(0,tempLoc)) == 0)
					{
						// remove receiver from temp 
						temp = temp.substr(tempLoc + splitters.at(i).length() + 2);
						// receiver was found
						foundReceiver = true;
					}
				}
			}
		}

	}

	if (temp.size() > 0)
	{
		// check against receivers one more time
		foundReceiver = false;
		for (size_t i = 0; i < receivers.size() && !foundReceiver; i++)
		{
			// if temp == receiver
			if (receivers.at(i).compare(temp) == 0)
			{
				// receiver was found
				foundReceiver = true;
			}
		}
	}

	return foundCaller && foundReceiver;
}
