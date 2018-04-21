/***********************************************************************************
File Name: Look.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Look - displays information corresponding to command
Procedures:	Look() - constructor
			~Look() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Look Command
************************************************************************************/

#pragma once
#include "Command.h"

class Look :
	public Command
{
public:
	Look();
	~Look();
	virtual bool action(string cmd, Player* player);
};

