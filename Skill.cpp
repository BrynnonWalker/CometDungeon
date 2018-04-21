/***********************************************************************************
File Name: Skill.cpp
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

#include <random>

#include "Skill.h"
/***********************************************************************************
Function: Skill
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor; sets to default values
Arguments:	none
************************************************************************************/
Skill::Skill()
{
	reset();
}

/***********************************************************************************
Function: Skill
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: constructor; sets to input values
Arguments:	(I/P):
				string name - name of skill
				int stamina - stamina required to use skill
				int min - minimum amount of damage skill can deal
				int max - maximum amount of damage skill can deal
************************************************************************************/
Skill::Skill(string name, int stamina, int min, int max)
{
	this->name = name;
	staminaRequired = stamina;
	attackDamageMin = min;
	attackDamageMax = max;
	// flip attack damage if not positive
	if (attackDamageMin < 0)
	{
		attackDamageMin *= -1;
	}
	if (attackDamageMax < 0)
	{
		attackDamageMin *= -1;
	}
	// make sure max > min
	if (attackDamageMin >= attackDamageMax)
	{
		attackDamageMax = attackDamageMin + 1;
	}
}

/***********************************************************************************
Function: ~Skill
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Skill::~Skill()
{
}

/***********************************************************************************
Function: reset
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets skill values to default values
Arguments:	none
************************************************************************************/
void Skill::reset()
{
	name = "basic attack";
	staminaRequired = 0;
	attackDamageMin = 1;
	attackDamageMax = 5;
}

/***********************************************************************************
Function: getName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns skill name
Arguments:	(O/P) string - skill name
************************************************************************************/
string Skill::getName()
{
	return name;
}

/***********************************************************************************
Function: getDamage
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns damage dealt by skill calculated randomly
Arguments:	(O/P) int - damage dealth by skill
************************************************************************************/
int Skill::getDamage()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(attackDamageMin, attackDamageMax);
	return dist(mt);
}

/***********************************************************************************
Function: getCost
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns cost of using skill
Arguments:	(O/P) int - skill cost
************************************************************************************/
int Skill::getCost()
{
	return staminaRequired;
}
