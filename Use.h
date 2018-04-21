/***********************************************************************************
File Name: Use.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Use - displays information corresponding to command
Procedures:	Use() - constructor
			~Use() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Use Command
************************************************************************************/
#pragma once
#include "Command.h"

class Use :
	public Command
{
public:
	Use();
	~Use();
	virtual bool action(string cmd, Player* player);
};

