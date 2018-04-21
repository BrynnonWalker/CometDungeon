/***********************************************************************************
File Name: Player.cpp
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

#include <math.h>
#include <random>

#include "Player.h"

using namespace std;

/***********************************************************************************
Function: Player
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: construct object, set default values
Arguments:	none
************************************************************************************/
Player::Player()
{
	// default player settings
	name = "player";
	level = 1;
	experience = 0;
	health = getMaxHealth();
	stamina = getMaxStamina();
	currentScene = nullptr;
	location = nullptr;
	weapon.setType(3);
	armor.setType(4);
	// bare hand damage
	weapon.setVal(5);
	inventory.clear();
	// default player class is CS
	setType(PlayerClasses::CS);
}

/***********************************************************************************
Function: ~Player
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Player::~Player()
{
}

/***********************************************************************************
Function: getMaxHealth
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: calculates max health
Arguments:	(O/P) int - returns max health
************************************************************************************/
int Player::getMaxHealth()
{
	int max = 50 + level * 50;

	max += armor.getMod() * 10;

	return max;
}

/***********************************************************************************
Function: getMaxStamina
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: calculate max stamina
Arguments:	(O/P) int - returns max stamina
************************************************************************************/
int Player::getMaxStamina()
{
	return 50 + (level * 10);
}

/***********************************************************************************
Function: findSkill
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks whether player has skill
Arguments:	(I/P) Skill * skill - skill to check against
			(O/P) bool - whether player has skill
************************************************************************************/
bool Player::findSkill(Skill * skill)
{
	for (size_t i = 0; i < skillList.size(); i++)
	{
		if (skillList.at(i).getName().compare(skill->getName()) == 0)
		{
			return true;
		}
	}

	return false;
}

/***********************************************************************************
Function: addSkill
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds skill to skill list
Arguments:	(I/P):
				 string name - skill name
				 int staminaReq - stamina required to use skill
				 int damageMin - minimum damage skill deals
				 int damageMax - maximum damage skill deals
************************************************************************************/
void Player::addSkill(string name, int staminaReq, int damageMin, int damageMax)
{
	Skill skill(name, staminaReq, damageMin, damageMax);
	skillList.emplace_back(skill);
}

/***********************************************************************************
Function: getLevelUPExp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: calculates experience required to level
Arguments:	(O/P) int - required experience
************************************************************************************/
int Player::getLevelUPExp()
{
	return 200 * (int) pow(2, level);
}

/***********************************************************************************
Function: attack
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: calculates damage player deals
Arguments:	(I/P) Skill* skill - skill player uses
			(O/P) int - damage player deals
************************************************************************************/
int Player::attack(Skill * skill)
{
	if (weapon.getMod() <= 1)
	{
		weapon.setVal(2);
	}
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, weapon.getMod());
	int baseDamage = dist(mt);
	if (findSkill(skill))
	{
		stamina -= skill->getCost();
		return baseDamage + skill->getDamage();
	}
	else
	{
		return baseDamage;
	}
}

/***********************************************************************************
Function: recover
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: recovers fixed health and stamina points
Arguments:	none
************************************************************************************/
void Player::recover()
{
	// recover 1/10 of max health points
	restoreHealth(getMaxHealth() / 10 + 1);
	// recover 1/2 of current stamina points
	restoreStamina(getMaxStamina() / 2 + 1);
}

/***********************************************************************************
Function: restoreStamina
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds value to stamina
Arguments:	(I/P) int restore - value to add to stamina
************************************************************************************/
void Player::restoreStamina(int restore)
{
	stamina += restore;
	if (stamina > getMaxStamina())
	{
		stamina = getMaxStamina();
	}
}

/***********************************************************************************
Function: isDead
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks if player is dead
Arguments:	(O/P) bool - checks whether health <= 0
************************************************************************************/
bool Player::isDead()
{
	return health <= 0;
}

/***********************************************************************************
Function: getStamina
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns stamina
Arguments:	(O/P) int - player current stamina
************************************************************************************/
int Player::getStamina()
{
	return stamina;
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets player name
Arguments:	(I/P) string name - new player name
************************************************************************************/
void Player::setName(string name)
{
	this->name = name;
}

/***********************************************************************************
Function: moveScene
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: move player to new scene
Arguments:	(I/P) Scene* newScene
************************************************************************************/
void Player::moveScene(Scene * newScene)
{
	bool foundStartRoom = false;
	currentScene = newScene;

	for (int i = 0; i < currentScene->getNumRooms() && !foundStartRoom; i++)
	{
		if (currentScene->getRoom(i)->getType().compare("start") == 0)
		{
			// found start room, move player location
			setLocation(currentScene->getRoomCoordinate(currentScene->getRoom(i)->getName()));
			foundStartRoom = true;
		}
	}
}

/***********************************************************************************
Function: getCurrentRoom
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: finds player's current room 
Arguments:	(O/P) Room* - pointer to player's current room
************************************************************************************/
Room * Player::getCurrentRoom()
{
	// for each room
	for (int i = 0; i < currentScene->getNumRooms(); i++)
	{
		// check if room is player's current room
		if (currentScene->getRoomCoordinate(currentScene->getRoom(i)->getName())->getX() == location->getX()
			&& currentScene->getRoomCoordinate(currentScene->getRoom(i)->getName())->getY() == location->getY())
		{
			// room coordinates match player's room coordinates
			return currentScene->getRoom(i);
		}
	}
	return nullptr;
}

/***********************************************************************************
Function: getCurrentScene
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets players current scene
Arguments:	(O/P) Scene* - returns pointer to current scene
************************************************************************************/
Scene * Player::getCurrentScene()
{
	return currentScene;
}

/***********************************************************************************
Function: setLocation
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets player location to corresponding location
Arguments:	(I/P) Coordinate* location - new location for player
************************************************************************************/
void Player::setLocation(Coordinate* location)
{
	this->location = location;
}

/***********************************************************************************
Function: setType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets player class and changes skills
Arguments:	(I/P) PlayerClasses type - new player class type
************************************************************************************/
void Player::setType(PlayerClasses type)
{
	skillList.clear();
	this->type = type;

	// set player values/skills to values of corresponding class
	switch (type)
	{
		case PlayerClasses::CS:
			addSkill("Basic Attack", 0, 1, 10);
			addSkill("Virus", 25, 45, 75);
			addSkill("Throw Computer", 15, 15, 50);
			addSkill("Program a Win", 100, 0, 1000);
			addSkill("Computer Talk", 10, 5, 25);
			break;
		case PlayerClasses::CE:
			addSkill("Basic Attack", 0, 1, 10);
			addSkill("Overclock", 30, 35, 95);
			addSkill("Engineer", 15, 5, 55);
			addSkill("Hack", 100, 0, 1000);
			addSkill("Quick Process", 5, 5, 15);
			break;
		case PlayerClasses::SE:
			addSkill("Basic Attack", 0, 1, 10);
			addSkill("UML Diagram", 35, 45, 45); // Consistent damage
			addSkill("Agile Attack", 5, 8, 12);
			addSkill("Implement", 100, 0, 1000);
			addSkill("Waterfall", 5, 10, 10);
			break;
		case PlayerClasses::ATEC:
			addSkill("Basic Attack", 0, 1, 10);
			addSkill("Design Punch", 20, 5, 65);
			addSkill("Hybrid Nerd", 15, 20, 25);
			addSkill("Capstone Project", 100, 0, 1000);
			addSkill("Animate", 10, 5, 35);
			break;
	}

}

/***********************************************************************************
Function: addItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds item to inventory
Arguments:	(I/P) Item* item - item to add
			(O/P) bool - whether item was added to inventory
************************************************************************************/
bool Player::addItem(Item * item)
{
	inventory.emplace_back(* item);
	return true;
}

/***********************************************************************************
Function: removeItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: remove item from inventory
Arguments:	(I/P) Item* item - item to remove
			(O/P) bool - whether item was removed
************************************************************************************/
bool Player::removeItem(Item * item)
{
	bool found = false;
	for (size_t i = 0; i < inventory.size() && !found; i++)
	{
		if (inventory.at(i).getFullname().compare(item->getFullname()) == 0)
		{
			// same item, take out of inventory
			inventory.erase(inventory.begin() + i);
			found = true;
		}
	}

	return found;
}

/***********************************************************************************
Function: getInventory
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get pointer to inventory
Arguments:	(O/P) vector<Item>* - pointer to inventory item list
************************************************************************************/
vector<Item>* Player::getInventory()
{
	return &inventory;
}

/***********************************************************************************
Function: getSkillList
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get pointer to skills
Arguments:	(O/P) vector<Skill>* - pointer to skill list
************************************************************************************/
vector<Skill>* Player::getSkillList()
{
	return &skillList;
}

/***********************************************************************************
Function: restoreHealth
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: restore health by value
Arguments:	(I/P) int restore - value to add to health
************************************************************************************/
void Player::restoreHealth(int restore)
{
	health += restore;
	if (health > getMaxHealth())
	{
		health = getMaxHealth();
	}
}

/***********************************************************************************
Function: hurt
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: lower player health by value
Arguments:	(I/P) int damage - value to decrease health by
************************************************************************************/
void Player::hurt(int damage)
{
	health -= damage;
}

/***********************************************************************************
Function: equip
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attempt to equip item
Arguments:	(I/P) Item* item - item to equip
************************************************************************************/
void Player::equip(Item * item)
{
	if (item->canEquip())
	{
		// item is equippable
		if (item->getType().compare("weapon") == 0)
		{
			// if weapon
			weapon.setFullname(item->getFullname());
			weapon.setName(item->getName());
			weapon.setDescr(item->getDesc());
			weapon.setVal(item->getMod());
		}
		else if(item->getType().compare("armor") == 0)
		{
			// if armor
			armor.setFullname(item->getFullname());
			armor.setName(item->getName());
			armor.setDescr(item->getDesc());
			armor.setVal(item->getMod());
		}
	}
}

/***********************************************************************************
Function: findItem
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: check inventory for item
Arguments:	(I/P) Item* item - item to be checked for
			(O/P) Item* - pointer to item in inventory, not found -> null
************************************************************************************/
Item * Player::findItem(Item * item)
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory.at(i).getFullname() == item->getFullname())
		{
			return &inventory.at(i);
		}
	}

	return nullptr;
}

/***********************************************************************************
Function: getLife
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get player's current health
Arguments:	(O/P) int - player health
************************************************************************************/
int Player::getLife()
{
	return health;
}

/***********************************************************************************
Function: getType
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get player class type
Arguments:	(O/P) string - string corresponding to player class
************************************************************************************/
string Player::getType()
{
	string temp;
	switch (type)
	{
	case PlayerClasses::CS:
		temp = "CS";
		break;
	case PlayerClasses::CE:
		temp = "CE";
		break;
	case PlayerClasses::SE:
		temp = "SE";
		break;
	case PlayerClasses::ATEC:
		temp = "ATEC";
		break;
	default:
		temp = "ERR";
		break;
	}

	return temp;
}

/***********************************************************************************
Function: getLevel
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: return level
Arguments:	(O/P) int - player level
************************************************************************************/
int Player::getLevel()
{
	return level;
}

/***********************************************************************************
Function: getExp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get player experience
Arguments:	(O/P) int - player experience
************************************************************************************/
int Player::getExp()
{
	return experience;
}

/***********************************************************************************
Function: addExp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: add experience to player and check for levelup
Arguments:	(I/P) int exp - experience to add
			(O/P) bool - whether player leveled up
************************************************************************************/
bool Player::addExp(int exp)
{
	bool levelUP = false;
	experience += exp;
	// check if level up
	if (experience >= getLevelUPExp())
	{
		// level up!
		level++;
		experience = 0;
		levelUP = true;
		// recover some health and stamina
		recover();
	}

	return levelUP;
}

/***********************************************************************************
Function: getWeapon
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get current weapon
Arguments:	(O/P) Item* - current weapon pointer
************************************************************************************/
Item * Player::getWeapon()
{
	return &weapon;
}

/***********************************************************************************
Function: getArmor
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: get current armor
Arguments:	(O/P) Item* - current armor pointer
************************************************************************************/
Item * Player::getArmor()
{
	return &armor;
}
