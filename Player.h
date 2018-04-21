/***********************************************************************************
File Name: Player.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Player - object for player data
Procedures:		Player() - constructor
				~Player() - destructor
				int getMaxHealth() - calculates maximum health for player
				int getMaxStamina() - calculates maximum stamina for player
				bool findSkill(Skill* skill) - checks whether player has skill
				void addSkill(string name, int staminaReq, int damageMin, int damageMax) - adds skill to player skill list
				void setName(string name) - sets player name
				void moveScene(Scene* newScene) - moves player scene tracker to new scene
				Room * getCurrentRoom() - returns pointer to room player is in
				Scene* getCurrentScene() - returns pointer to scene player is in
				void setLocation(Coordinate* location) - sets player location to corresponding location on map
				void setType(PlayerClasses type) - sets player class type
				bool addItem(Item* item) - attempts to add item to inventory
				bool removeItem(Item* item) - attempts to remove item from inventory
				vector<Item>* getInventory() - returns pointer to inventory
				vector<Skill>* getSkillList() - returns pointer to skill list
				void restoreHealth(int restore) - adds value to health
				void hurt(int damage) - removes value from health
				void equip(Item* item) - equips item
				Item* findItem(Item* item) - locates item in inventory
				int getLife() - returns player health
				string getType() - returns player class type
				int getLevel() - returns player level
				int getExp() - returns player experience points
				bool addExp(int exp) - adds experience to player
				Item* getWeapon() - returns pointer to player equipped item
				Item* getArmor() - returns pointer to player equipped item
				int getLevelUPExp() - calculates experience required to level up
				int attack(Skill* skill) - calculates damage the attack does
				void recover() - recovers player health and stamina by fixed amount
				void restoreStamina(int restore) - adds value to stamina
				bool isDead() - checks if player health has reached or gone below 0
				int getStamina() - returns stamina
************************************************************************************/

#pragma once

#include "Scene.h"
#include "Room.h"
#include "Coordinate.h"
#include "PlayerClasses.h"
#include "Skill.h"

class Player
{
private:
	string name;
	PlayerClasses type;
	int level;
	int experience;
	int health, stamina;
	Scene* currentScene;
	Coordinate* location;
	vector<Item> inventory;
	vector<Skill> skillList;
	Item weapon;
	Item armor;
	int getMaxHealth();
	int getMaxStamina();
	bool findSkill(Skill* skill);
	void addSkill(string name, int staminaReq, int damageMin, int damageMax);
public:
	Player();
	~Player();
	void setName(string name);
	void moveScene(Scene* newScene);
	Room * getCurrentRoom();
	Scene* getCurrentScene();
	void setLocation(Coordinate* location);
	void setType(PlayerClasses type);
	bool addItem(Item* item);
	bool removeItem(Item* item);
	vector<Item>* getInventory();
	vector<Skill>* getSkillList();
	void restoreHealth(int restore);
	void hurt(int damage);
	void equip(Item* item);
	Item* findItem(Item* item);
	int getLife();
	string getType();
	int getLevel();
	int getExp();
	bool addExp(int exp);
	Item* getWeapon();
	Item* getArmor();
	int getLevelUPExp();
	int attack(Skill* skill);
	void recover();
	void restoreStamina(int restore);
	bool isDead();
	int getStamina();
};
