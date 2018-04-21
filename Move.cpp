/***********************************************************************************
File Name: Move.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Move - attempts to move the player
Procedures:	Move() - constructor
			~Move() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Look Command
************************************************************************************/


#include "Move.h"

#include <iostream>

using namespace std;

/***********************************************************************************
Function: Move
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Move::Move()
{
	// add default callers/receivers for movement
	// default callers for moving
	addCmdName("move");
	addCmdName("go");
	// the 4 default directions of movement
	addReceiver("north");
	addReceiver("south");
	addReceiver("east");
	addReceiver("west");

	setName("move");
	setDesc("'move <direction>' ---- used for player movement");
}

/***********************************************************************************
Function: ~Move
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Move::~Move()
{
}
/***********************************************************************************
Function: action
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempts to use the Move command
Arguments:	(I/P):
				string cmd - command that is being parsed
				Player* player - pointer to player object
			(O/P) bool - if command was successful
************************************************************************************/
bool Move::action(string cmd, Player* player)
{
	bool found = false;
	Room* roomPtr;
	vector<Pathway>* pathsPtr;
	string direction;

	// make sure cmd is valid
	if (checkCommand(cmd))
	{
		direction = removeCaller(cmd);

		// find room
		roomPtr = player->getCurrentRoom();
		// get paths
		pathsPtr = roomPtr->getPaths();
		// check paths direction with cmd direction
		for (size_t i = 0; i < pathsPtr->size() && !found; i++)
		{
			if (pathsPtr->at(i).getDirection().compare(direction) == 0)
			{
				// direction matches
				found = true;
				// set direction to exit room
				direction = pathsPtr->at(i).getExit();
				player->setLocation(player->getCurrentScene()->getRoomCoordinate(direction));
				// reset roomPtr for event call
				roomPtr = player->getCurrentRoom();

				// if room has not been entered before, player recovers some health and stamina
				if (!roomPtr->isVisited())
				{
					player->recover();
				}

				// enter the room
				roomPtr->enter();
			}
		}

		if (!found)
		{
			// path room not found
			return false;
		}

	}
	else
	{
		// not valid cmd
		return false;
	}

	return true;
}
