/***********************************************************************************
File Name: Help.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Help - displays command descriptions
Procedures:	Help() - constructor
			~Help() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Help Command
************************************************************************************/

#pragma once
#include "Command.h"

class Help :
	public Command
{
public:
	Help();
	~Help();
	virtual bool action(string cmd, Player* player); // attempt to use the Help Command
};

