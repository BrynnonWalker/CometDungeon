/***********************************************************************************
File Name: Get.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Get - command that attempts to add an object to player inventory
Procedures:	Get() - constructor
			~Get() - destuctor
			virtual bool action(string cmd, Player* player) - attempt to use the Get Command
************************************************************************************/



#pragma once
#include "Command.h"

class Get :
	public Command
{
public:
	Get();
	~Get();
	virtual bool action(string cmd, Player* player); // attempt to use the Get Command
};

