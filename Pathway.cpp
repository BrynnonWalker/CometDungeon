/***********************************************************************************
File Name: Pathway.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Pathway - paths between rooms
Procedures:		Pathway() - constructor
				~Pathway() - destructor
				string getName() - gets path nae
				void setName(string name) - sets path name
				void setDesc(string descr) - sets path description
				string getExit() - gets exit
				void setRoom(string exit) - sets connecting room
				void setDirection(string dir) - sets current direction
				string getDirection() - gets current direction
				void clear() - resets paths to default
				bool isConnected() - checks if room is connected
				void connect(string room) - connects two rooms
				void display() - displays paths
				void close() - close a path
************************************************************************************/

#include <iostream>

#include "Pathway.h"

using namespace std;

/***********************************************************************************
Function: Pathway
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	none
************************************************************************************/
Pathway::Pathway()
{
	clear();
}

/***********************************************************************************
Function: ~Pathway
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Pathway::~Pathway()
{
}

/***********************************************************************************
Function: getName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor, sets default values for callers and descriptions
Arguments:	(O/P) string - returns path name
************************************************************************************/
string Pathway::getName()
{
	return name;
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets path name
Arguments:	(I/P) string name - name of path
************************************************************************************/
void Pathway::setName(string name)
{
	this->name = name;
}

/***********************************************************************************
Function: setDesc
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets path name
Arguments:	(I/P) string descr - description of path
************************************************************************************/
void Pathway::setDesc(string descr)
{
	description = descr;
}

/***********************************************************************************
Function: getExit
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get exit room name
Arguments:	(O/P) string - name of exit room
************************************************************************************/
string Pathway::getExit()
{
	return exit;
}

/***********************************************************************************
Function: setRoom
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets exit room
Arguments:	(I/P) string exit - name of exit room
************************************************************************************/
void Pathway::setRoom(string exit)
{
	this->exit = exit;
}

/***********************************************************************************
Function: setDirection
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets path direction
Arguments:	(I/P) string dir - direction of path
************************************************************************************/
void Pathway::setDirection(string dir)
{
	direction = dir;
}

/***********************************************************************************
Function: getName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets path direction
Arguments:	(O/P) string - name of path direction
************************************************************************************/
string Pathway::getDirection()
{
	return direction;
}

/***********************************************************************************
Function: clear
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: clears to default values
Arguments:	none
************************************************************************************/
void Pathway::clear()
{
	name = "";
	exit = "";
	description = "";
	direction = "";
	connected = false;
}

/***********************************************************************************
Function: isConnected
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if exit room exits
Arguments:	(O/P) bool - if there is an exit room
************************************************************************************/
bool Pathway::isConnected()
{
	return exit.length() > 0;
}

/***********************************************************************************
Function: connect
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets connecting room
Arguments:	(O/P) string room - name of connecting room
************************************************************************************/
void Pathway::connect(string room)
{
	exit = room;
	connected = true;
}

/***********************************************************************************
Function: display
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: displays path direction
Arguments:	none
************************************************************************************/
void Pathway::display()
{
	if (exit.length() > 0)
	{
		cout << "There is a path to the " << direction << endl;
	}
}

/***********************************************************************************
Function: close
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: closes the path
Arguments:	none
************************************************************************************/
void Pathway::close()
{
	connected = true;
	exit = "";
}
