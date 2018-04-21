/***********************************************************************************
File Name: Entity.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Entity - Object for enemy creatures
Procedures:	Entity() - default constructor
			Entity(string name, int health, int stamina) - constructor with parameters
			~Entity() - destructor
			void setName(string name) - sets name
			void flipVisible() - flips entity visibility
			bool isVisible() - checks if visible
			string getName() - gets entity name
			int getLife() - gets entity health
			void clear() - reset entity data to default values
			int attack() - used to simulate an entity attack
			void hurt(int damage) - lowers health of entity
			bool isDead() - checks if health is <= 0
			void addSkill(string skill) - adds to entity skill list
************************************************************************************/


#include <iostream>
#include <random>

#include "Entity.h"

using namespace std;

/***********************************************************************************
Function: Entity
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor
Arguments:	none
************************************************************************************/
Entity::Entity()
{
	clear();
}

/***********************************************************************************
Function: Entity
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: constructor
Arguments:	(I/P):
				string name - name of entity
				int health - entity health
				int stamina - entity stamina
************************************************************************************/
Entity::Entity(string name, int health, int stamina)
{
	this->name = name;
	this->health = health;
	this->stamina = stamina;
}

/***********************************************************************************
Function: ~Entity
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Entity::~Entity()
{
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets entity name
Arguments:	(I/P) string name - entity name
************************************************************************************/
void Entity::setName(string name)
{
	this->name = name;
}

/***********************************************************************************
Function: flipVisible
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: flips entity visibility
Arguments:	none
************************************************************************************/
void Entity::flipVisible()
{
	visible = !visible;
}

/***********************************************************************************
Function: isVisible
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if entity is visible
Arguments:	(O/P) bool - returns visibility
************************************************************************************/
bool Entity::isVisible()
{
	return visible;
}

/***********************************************************************************
Function: getName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets entity name
Arguments:	(O/P) string - returns entity name
************************************************************************************/
string Entity::getName()
{
	return name;
}

/***********************************************************************************
Function: getLife
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets entity health
Arguments:	(O/P) int - returns entity health
************************************************************************************/
int Entity::getLife()
{
	return health;
}

/***********************************************************************************
Function: clear
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: reset entity data to default values
Arguments:	none
************************************************************************************/
void Entity::clear()
{
	visible = true;
	name = "";
	health = 1;
	skillList.clear();
}

/***********************************************************************************
Function: attack
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: simulates attack sequence
Arguments:	(O/P) int - returns entity attack damage
************************************************************************************/
int Entity::attack()
{
	int skill;
	int tries = 5;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 10);
	// if entity has skills and has not tried to pick one more than 5 times
	while (skillList.size() > 0 && tries > 0)
	{
		// pick skill
		uniform_int_distribution<int> dist2(0, skillList.size() - 1);
		skill = dist2(mt);

		// check if entity has enough stamina
		if (stamina >= skillList.at(skill).getCost())
		{
			// has enough, return skill damage + base damage
			cout << name << " used " << skillList.at(skill).getName() << endl;
			stamina -= skillList.at(skill).getCost();
			return dist(mt) + skillList.at(skill).getDamage();
		}


		// skill has not been chosen, lower number of tries left
		tries--;

	}

	// entity has no skills or didn't pick one!
	return dist(mt);
}

/***********************************************************************************
Function: hurt
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: lowers health of entity
Arguments:	(I/P) int damage - amount of damage dealt to entity
************************************************************************************/
void Entity::hurt(int damage)
{
	health -= damage;
}

/***********************************************************************************
Function: isDead
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Checks if entity is dead
Arguments:	(O/P) bool - returns if entity is dead
************************************************************************************/
bool Entity::isDead()
{
	return health <= 0;
}

/***********************************************************************************
Function: addSkill
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds skill to entity skill list
Arguments:	(I/P) string skill - skill name to be added to list
************************************************************************************/
void Entity::addSkill(string skill)
{
	string temp;
	string name;
	int damageMin, damageMax, staminaReq;

	name = skill.substr(0,skill.find_first_of("|"));
	temp = skill.substr(skill.find_first_of("|") + 1);
	staminaReq = atoi(temp.substr(0, temp.find_first_of("|")).c_str());
	temp = temp.substr(temp.find_first_of("|") + 1);
	damageMin = atoi(temp.substr(0, temp.find_first_of("|")).c_str());
	temp = temp.substr(temp.find_first_of("|") + 1);
	damageMax = atoi(temp.substr(0, temp.find_first_of("|")).c_str());

	skillList.emplace_back(Skill(name, staminaReq, damageMin, damageMax));

}
