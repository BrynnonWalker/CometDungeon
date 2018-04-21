/***********************************************************************************
File Name: Skill.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Skill - attack moves and their data
Procedures:		Skill() - default constructor
				Skill(string name, int stamina, int min, int max) - constructor with parameters
				~Skill() - destructor
				void reset() - resets attack data to default values
				string getName() - returns name of skill
				int getDamage() - returns the amount of damage dealt
				int getCost() - returns the cost of using the skill
************************************************************************************/
#pragma once

#include <string>

using namespace std;

class Skill
{
private:
	string name;
	int staminaRequired;
	int attackDamageMin, attackDamageMax;
public:
	Skill();
	Skill(string name, int stamina, int min, int max);
	~Skill();
	void reset();
	string getName();
	int getDamage();
	int getCost();
};

