/***********************************************************************************
File Name: Move.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Move - attempt to move player
Procedures:	Move() - constructor
			~Move() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Look Command
************************************************************************************/


#pragma once
#include "Command.h"

class Move :
	public Command
{
public:
	Move();
	~Move();
	virtual bool action(string cmd, Player* player); // attempt to use the Move Command
};

