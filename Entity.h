/***********************************************************************************
File Name: Entity.h
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

#pragma once

#include <string>
#include <vector>

#include "Skill.h"

using namespace std;

class Entity
{
private:
	string name;
	int health, stamina;
	bool visible;
	vector<Skill> skillList;
public:
	Entity();
	Entity(string name, int health, int stamina);
	~Entity();
	void setName(string name);
	void flipVisible();
	bool isVisible();
	string getName();
	int getLife();
	void clear();
	int attack();
	void hurt(int damage);
	bool isDead();
	void addSkill(string skill);
};

