/***********************************************************************************
File Name: Scene.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Scene - contains rooms and map of rooms
Procedures:	Scene() - default constructor
			~Scene() - destructor
			Room* getRoom(string roomName) - returns room corresponding to name
			void fixMapPathing(Room* roomPtr) - checks for unconnected paths in the room
			void displayLevel(int level, int current, int end, Room* currentRoom) - recursively displays level of map
			void displayMap(Room* currentRoom) - calls displayLevel for each level
			bool buildMap() - builds the scene map
			void setName(string str) - set scene name
			bool addRoom(Room room) - adds room to scene's room list
			bool addMultiRoom(Room room, int num) - adds rooms to scene room list based on input value
			string getRoomFilename() - returns scene name
			int getNumRooms() - returns number of rooms in scene
			Room* getRoom(int numRoom) - returns room at input location in rooms vector
			Coordinate* getRoomCoordinate(string roomName) - returns coordinate of room
			void clear() - resets room to default values
			void showMap() - displays the coordinates of rooms (used for debugging)
			void setOrder(int order) - sets order of scene
			int getOrder() - returns order of scene
************************************************************************************/
#include "Scene.h"

#include <random>
#include <iostream>

using namespace std;

/***********************************************************************************
Function: Scene
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: default constructor; sets to default values
Arguments:	none
************************************************************************************/
Scene::Scene()
{
	clear();
}

/***********************************************************************************
Function: ~Scene
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: destructor
Arguments:	none
************************************************************************************/
Scene::~Scene()
{
}

/***********************************************************************************
Function: displayMap
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: calls displayLevel for each level
Arguments:	(I/P) Room* currentRoom - pointer to room player is currently in
************************************************************************************/
void Scene::displayMap(Room* currentRoom)
{
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;
	// check if map is empty
	if (!map.empty())
	{
		// get min, max coord for x and y
		for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end(); it++)
		{
			if (it->second.getX() < minX)
			{
				minX = it->second.getX();
			}
			if (it->second.getX() > maxX)
			{
				maxX = it->second.getX();
			}
			if (it->second.getY() > maxY)
			{
				maxY = it->second.getY();
			}
			if (it->second.getY() < minY)
			{
				minY = it->second.getY();
			}
		}
		// call recursive function to display floor map by level
		// top to bottom
		cout << "Map: " << endl;
		for (int i = maxY; i >= minY; i--)
		{
			displayLevel(i, minX, maxX, currentRoom);
			cout << endl;
		}
	}
}

/***********************************************************************************
Function: buildMap
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: attemps to build randomized map
Arguments:	(I/P) bool - whether map was built or not
************************************************************************************/
bool Scene::buildMap()
{
	Coordinate coord(0, 0);
	Room* ptr = &rooms.at(0);
	bool found = false;
	bool found2;
	bool filled = false;
	vector<Room*> checked, checked2;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, rooms.size()-1);
	int randRoom;

	map.clear();
	
	// get start room
	for (size_t i = 0; i < rooms.size() && !found; i++)
	{
		if (rooms.at(i).getType().compare("start") == 0)
		{
			// start room found
			ptr = &rooms.at(i);
			map[ptr] = coord;
			found = true;
		}
	}

	// add random rooms
	while (map.size() < rooms.size()-1 && map.size() > 0)
	{
		// get ptr to unchecked room on map
		found = false;
		for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !found; it++)
		{
			if (checked.size() == 0)
			{
				ptr = it->first;
				found = true;
				checked.push_back(ptr);
			}
			else
			{
				// check current room against all names in vector
				found2 = false;
				for (size_t i = 0; i < checked.size() && !found2; i++)
				{
					if (checked.at(i)->getName().compare(it->first->getName()) == 0)
					{
						// found it on list
						found2 = true;
					}
				}

				if (!found2)
				{
					// this room has not been checked
					found = true;
					ptr = it->first;
					checked.push_back(ptr);
				}
			}
		}

		if (!found)
		{
			// all have been checked
			break;
		}

		filled = false;
		checked2.clear();
		// for each room already on map, put into checked2
		for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end(); it++)
		{
			checked2.push_back(it->first);
		}
		while(!filled)
		{
			coord = map[ptr];

			// for each path of the current room, try to add random rooms onto it
			randRoom = dist(mt);
			found = false;
			// if end room, do not add yet
			if (rooms.at(randRoom).getType().compare("end") == 0)
			{
				found = true;
			}

			// check if room has already been tested against
			for (size_t i = 0; i < checked2.size() && !found; i++)
			{
				if (checked2.at(i)->getName().compare(rooms.at(randRoom).getName()) == 0)
				{
					// room is already checked against
					found = true;
				}
			}


			if (!found)
			{
				// room not in map
				// for each path in current room, check if rand room can be connected
				for (size_t i = 0; i < ptr->getPaths()->size() && !found; i++)
				{
					// if not already in use
					if (!ptr->getPaths()->at(i).isConnected())
					{
						// check for opposite paths
						if (ptr->getPaths()->at(i).getDirection().compare("north") == 0)
						{
							for (size_t j = 0; j < rooms.at(randRoom).getPaths()->size() && !found; j++)
							{
								if (!rooms.at(randRoom).getPaths()->at(j).isConnected() && 
									rooms.at(randRoom).getPaths()->at(j).getDirection().compare("south") == 0)
								{
									// room can be added, so add it
									found = true;
									coord.up(1);
									map[&rooms.at(randRoom)] = coord;
									// connect up pathways
									rooms.at(randRoom).getPaths()->at(j).connect(ptr->getName());
									ptr->getPaths()->at(i).connect(rooms.at(randRoom).getName());
									// look for other pathways already on map
									fixMapPathing(&rooms.at(randRoom));
								}
							}
						}
						else if (ptr->getPaths()->at(i).getDirection().compare("south") == 0)
						{
							for (size_t j = 0; j < rooms.at(randRoom).getPaths()->size() && !found; j++)
							{
								if (!rooms.at(randRoom).getPaths()->at(j).isConnected() &&
									rooms.at(randRoom).getPaths()->at(j).getDirection().compare("north") == 0)
								{
									// room can be added, so add it
									found = true;
									coord.down(1);
									map[&rooms.at(randRoom)] = coord;
									// connect up pathways
									rooms.at(randRoom).getPaths()->at(j).connect(ptr->getName());
									ptr->getPaths()->at(i).connect(rooms.at(randRoom).getName());
									// look for other pathways already on map
									fixMapPathing(&rooms.at(randRoom));
								}
							}
						}
						else if (ptr->getPaths()->at(i).getDirection().compare("east") == 0)
						{
							for (size_t j = 0; j < rooms.at(randRoom).getPaths()->size() && !found; j++)
							{
								if (!rooms.at(randRoom).getPaths()->at(j).isConnected() &&
									rooms.at(randRoom).getPaths()->at(j).getDirection().compare("west") == 0)
								{
									// room can be added, so add it
									found = true;
									coord.right(1);
									map[&rooms.at(randRoom)] = coord;
									// connect up pathways
									rooms.at(randRoom).getPaths()->at(j).connect(ptr->getName());
									ptr->getPaths()->at(i).connect(rooms.at(randRoom).getName());
									// look for other pathways already on map
									fixMapPathing(&rooms.at(randRoom));
								}
							}
						}
						else if (ptr->getPaths()->at(i).getDirection().compare("west") == 0)
						{
							for (size_t j = 0; j < rooms.at(randRoom).getPaths()->size() && !found; j++)
							{
								if (!rooms.at(randRoom).getPaths()->at(j).isConnected() &&
									rooms.at(randRoom).getPaths()->at(j).getDirection().compare("east") == 0)
								{
									// room can be added, so add it
									found = true;
									coord.left(1);
									map[&rooms.at(randRoom)] = coord;
									// connect up pathways
									rooms.at(randRoom).getPaths()->at(j).connect(ptr->getName());
									ptr->getPaths()->at(i).connect(rooms.at(randRoom).getName());
									// look for other pathways already on map
									fixMapPathing(&rooms.at(randRoom));
								}
							}
						}
					}
				}

				// add room to checked2
				checked2.push_back(&rooms.at(randRoom));

			}
			// check if all pathways are filled
			filled = true;
			for (size_t i = 0; i < ptr->getPaths()->size() && filled; i++)
			{
				if (!ptr->getPaths()->at(i).isConnected())
				{
					filled = false;
				}
			}

			// check if all rooms checked against
			if (!filled && checked2.size() == rooms.size()-1)
			{
				//cout << "Room not completely filled, but no possible connections found!" << endl;
				filled = true;
			}
		}
	}

	// add end room
	found = false;
	for (size_t i = 0; i < rooms.size() && !found; i++)
	{
		if (rooms.at(i).getType().compare("end") == 0)
		{
			// end room found, attempt to add it to map
			ptr = &rooms.at(i);
			for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !found; it++)
			{
				// for each path in room on map
				for (size_t j = 0; j < it->first->getPaths()->size() && !found; j++)
				{
					// check if already used
					if (!it->first->getPaths()->at(j).isConnected())
					{
					
						// not connected, check against end room paths
						if (it->first->getPaths()->at(j).getDirection().compare("north") == 0)
						{
						
							for (size_t k = 0; k < ptr->getPaths()->size() && !found; k++)
							{
								if (ptr->getPaths()->at(k).getDirection().compare("south") == 0)
								{
									// connect it
									found = true;
									coord = map[it->first];
									coord.up(1);
									map[ptr] = coord;
									// connect end room path with current map room
									ptr->getPaths()->at(k).connect(it->first->getName());
									// connect current map room with end room path
									it->first->getPaths()->at(j).connect(ptr->getName());
									// look for other pathways already on map
									fixMapPathing(ptr);
								}
							}
						}
						else if (it->first->getPaths()->at(j).getDirection().compare("south") == 0)
						{
							for (size_t k = 0; k < ptr->getPaths()->size() && !found; k++)
							{
								if (ptr->getPaths()->at(k).getDirection().compare("north") == 0)
								{
									// connect it
									found = true;
									coord = map[it->first];
									coord.down(1);
									map[ptr] = coord;
									// connect end room path with current map room
									ptr->getPaths()->at(k).connect(it->first->getName());
									// connect current map room with end room path
									it->first->getPaths()->at(j).connect(ptr->getName());
									// look for other pathways already on map
									fixMapPathing(ptr);
								}
							}
						}
						else if (it->first->getPaths()->at(j).getDirection().compare("east") == 0)
						{
							for (size_t k = 0; k < ptr->getPaths()->size() && !found; k++)
							{
								if (ptr->getPaths()->at(k).getDirection().compare("west") == 0)
								{
									// connect it
									found = true;
									coord = map[it->first];
									coord.right(1);
									map[ptr] = coord;
									// connect end room path with current map room
									ptr->getPaths()->at(k).connect(it->first->getName());
									// connect current map room with end room path
									it->first->getPaths()->at(j).connect(ptr->getName());
									// look for other pathways already on map
									fixMapPathing(ptr);
								}
							}
						}
						else if (it->first->getPaths()->at(j).getDirection().compare("west") == 0)
						{
							for (size_t k = 0; k < ptr->getPaths()->size() && !found; k++)
							{
								if (ptr->getPaths()->at(k).getDirection().compare("east") == 0)
								{
									// connect it
									found = true;
									coord = map[it->first];
									coord.left(1);
									map[ptr] = coord;
									// connect end room path with current map room
									ptr->getPaths()->at(k).connect(it->first->getName());
									// connect current map room with end room path
									it->first->getPaths()->at(j).connect(ptr->getName());
									// look for other pathways already on map
									fixMapPathing(ptr);
								}
							}
						}
					}
				}
			}
			
			if(found)
			{
				map[ptr] = coord;
			}
			found = true;
		}
	}
	
	// check that end room exists
	found = false;
	for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !found; it++)
	{
		if(it->first->getType().compare("end") == 0)
		{
		
			// end room is in map!
			found = true;
		}
	}
	
	return found;
}

/***********************************************************************************
Function: setName
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets name of scene
Arguments:	(I/P) string str - name of scene
************************************************************************************/
void Scene::setName(string str)
{
	name = str;
}

/***********************************************************************************
Function: addRoom
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds room to scene
Arguments:	(I/P) Room room - room to be added
			(O/P) bool - whether room was added
************************************************************************************/
bool Scene::addRoom(Room room)
{
	bool found = false;
	// check if room already exists
	for (size_t i = 0; i < rooms.size() && !found; i++)
	{
		if (rooms.at(i).getName().compare(room.getName()) == 0)
		{
			// room names match, same room
			found = true;
		}
	}
	if (!found)
	{
		// room not found, add it
		rooms.push_back(room);
	}
	return !found;
}

/***********************************************************************************
Function: addMultiRoom
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds rooms to scene room list based on input value
Arguments:	(I/P):
				Room room - multi room to be added
				int num - number of this room to be added
			(O/P) bool - whether rooms were added correctly
************************************************************************************/
bool Scene::addMultiRoom(Room room, int num)
{
	string temp = "_cpy";
	while (num > 0)
	{
		bool found = false;
		// check if room already exists
		for (size_t i = 0; i < rooms.size() && !found; i++)
		{
			if (rooms.at(i).getName().compare(room.getName()) == 0)
			{
				// room names match, same room
				found = true;
				// change room name
				room.setName(room.getName() + temp);
			}
		}
		if (!found)
		{
			// room not found, add copy of it
			rooms.emplace_back(room);
			num--;
		}
	}
	return true;
}

/***********************************************************************************
Function: getRoomFilename
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns filename of room
Arguments:	(O/P) string - filename of room
************************************************************************************/
string Scene::getRoomFilename()
{
	return name + "_rooms.txt";
}

/***********************************************************************************
Function: getNumRooms
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns number of rooms in scene
Arguments:	(O/P) int - number of rooms in scene
************************************************************************************/
int Scene::getNumRooms()
{
	return rooms.size();
}

/***********************************************************************************
Function: getRoom
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns pointer to room at given index of vector
Arguments:	(I/P) int numRoom - index of room
			(O/P) Room* - pointer to room at index of vector
************************************************************************************/
Room* Scene::getRoom(int numRoom)
{
	if (numRoom < 0 || numRoom >= rooms.size())
	{
		return NULL;
	}

	return &rooms.at(numRoom);
}

/***********************************************************************************
Function: getRoom
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns a pointer to the room corresponding to room name
Arguments:	(I/P) string roomName - name of room
			(O/P) Room* - pointer to desired room
************************************************************************************/
Room* Scene::getRoom(string roomName)
{
	for (size_t i = 0; i < rooms.size(); i++)
	{
		if (rooms.at(i).getName().compare(roomName) == 0)
		{
			return &rooms.at(i);
		}
	}

	return NULL;
}

/***********************************************************************************
Function: fixMapPathing
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: checks for unconnected paths in the room
Arguments:	(I/P) Room* roomPtr - pointer to room being checked
************************************************************************************/
void Scene::fixMapPathing(Room * roomPtr)
{
	Coordinate roomCoords = map[roomPtr];;
	bool connectPath;

	// for each path of this room
	for (size_t i = 0; i < roomPtr->getPaths()->size(); i++)
	{
		// reset flag
		connectPath = false;
		// if the path is not connected
		if (!roomPtr->getPaths()->at(i).isConnected())
		{
			// check path direction
			if (roomPtr->getPaths()->at(i).getDirection().compare("north") == 0)
			{
				// look for a room to the north (y+1)
				// for every room in map 
				for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !connectPath; it++)
				{
					// check if map room coords match intended location
					if (it->second.getX() == roomCoords.getX() &&
						it->second.getY() == roomCoords.getY() + 1)
					{
						// this room is located there!
						// check if it has a path
						for (size_t j = 0; j < it->first->getPaths()->size() && !connectPath; j++)
						{
							// if path not connected and matches intended direction
							if (!it->first->getPaths()->at(j).isConnected() &&
								it->first->getPaths()->at(j).getDirection().compare("south") == 0)
							{
								// connect the two rooms
								connectPath = true;
								// connect room path with current map room
								roomPtr->getPaths()->at(i).connect(it->first->getName());
								// connect current map room with room path
								it->first->getPaths()->at(j).connect(roomPtr->getName());

							}
						}

						if (!connectPath)
						{
							// target room cannot connect up!
							// close this room's path, so that no other rooms take it
							roomPtr->getPaths()->at(i).close();
						}
					}
				}
			}
			else if (roomPtr->getPaths()->at(i).getDirection().compare("south") == 0)
			{
				// look for a room to the south (y-1)
				// for every room in map 
				for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !connectPath; it++)
				{
					// check if map room coords match intended location
					if (it->second.getX() == roomCoords.getX() &&
						it->second.getY() == roomCoords.getY() - 1)
					{
						// this room is located there!
						// check if it has a path
						for (size_t j = 0; j < it->first->getPaths()->size() && !connectPath; j++)
						{
							// if path not connected and matches intended direction
							if (!it->first->getPaths()->at(j).isConnected() &&
								it->first->getPaths()->at(j).getDirection().compare("north") == 0)
							{
								// connect the two rooms
								connectPath = true;
								// connect room path with current map room
								roomPtr->getPaths()->at(i).connect(it->first->getName());
								// connect current map room with room path
								it->first->getPaths()->at(j).connect(roomPtr->getName());

							}
						}

						if (!connectPath)
						{
							// target room cannot connect up!
							// close this room's path, so that no other rooms take it
							roomPtr->getPaths()->at(i).close();
						}
					}
				}
			}
			else if (roomPtr->getPaths()->at(i).getDirection().compare("east") == 0)
			{
				// look for a room to the east (x+1)
				// for every room in map 
				for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !connectPath; it++)
				{
					// check if map room coords match intended location
					if (it->second.getX() == roomCoords.getX() + 1 &&
						it->second.getY() == roomCoords.getY())
					{
						// this room is located there!
						// check if it has a path
						for (size_t j = 0; j < it->first->getPaths()->size() && !connectPath; j++)
						{
							// if path not connected and matches intended direction
							if (!it->first->getPaths()->at(j).isConnected() &&
								it->first->getPaths()->at(j).getDirection().compare("west") == 0)
							{
								// connect the two rooms
								connectPath = true;
								// connect room path with current map room
								roomPtr->getPaths()->at(i).connect(it->first->getName());
								// connect current map room with room path
								it->first->getPaths()->at(j).connect(roomPtr->getName());

							}
						}

						if (!connectPath)
						{
							// target room cannot connect up!
							// close this room's path, so that no other rooms take it
							roomPtr->getPaths()->at(i).close();
						}
					}
				}
			}
			else if (roomPtr->getPaths()->at(i).getDirection().compare("west") == 0)
			{
				// look for a room to the west (x-1)
				// for every room in map 
				for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !connectPath; it++)
				{
					// check if map room coords match intended location
					if (it->second.getX() == roomCoords.getX() - 1 &&
						it->second.getY() == roomCoords.getY())
					{
						// this room is located there!
						// check if it has a path
						for (size_t j = 0; j < it->first->getPaths()->size() && !connectPath; j++)
						{
							// if path not connected and matches intended direction
							if (!it->first->getPaths()->at(j).isConnected() &&
								it->first->getPaths()->at(j).getDirection().compare("east") == 0)
							{
								// connect the two rooms
								connectPath = true;
								// connect room path with current map room
								roomPtr->getPaths()->at(i).connect(it->first->getName());
								// connect current map room with room path
								it->first->getPaths()->at(j).connect(roomPtr->getName());

							}
						}

						if (!connectPath)
						{
							// target room cannot connect up!
							// close this room's path, so that no other rooms take it
							roomPtr->getPaths()->at(i).close();
						}
					}
				}
			}
		}
	}

}

/***********************************************************************************
Function: displayLevel
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: recursively displays level of map
Arguments:	(I/P):
				int level - level being displayed
				int current - current x-coordinate
				int end - final x-coordinate
				Room* currentRoom - room player is currently in
************************************************************************************/
void Scene::displayLevel(int level, int current, int end, Room* currentRoom)
{
	bool found = false;
	// check base condition
	if (current > end)
	{
		return;
	}
	// find matching room
	for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end() && !found; it++)
	{
		if (it->second.getX() == current && it->second.getY() == level)
		{
			// room found
			// check if player is in this room
			if (current == map[currentRoom].getX() && level == map[currentRoom].getY())
			{
				// player is in this room
				cout << "P";
			}
			else
			{
				// not player room, display room
				cout << "#";
			}
			found = true;
		}
	}
	if (!found)
	{
		// room not found, display empty
		cout << " ";
	}

	// recursively call towards end
	displayLevel(level, current + 1, end, currentRoom);
}

/***********************************************************************************
Function: getRoomCoordinate
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns coordinate of room
Arguments:	(I/P) string roomName - name of room
			(O/P) Coordinate* - pointer to coordinate of requested room
************************************************************************************/
Coordinate* Scene::getRoomCoordinate(string roomName)
{
	bool found = false;
	Room* ptr;
	// find room
	for (size_t i = 0; i < rooms.size() && !found; i++)
	{
		if (rooms.at(i).getName().compare(roomName) == 0)
		{
			// room found
			found = true;
			ptr = &rooms.at(i);
		}
	}

	if (map.find(ptr) == map.end())
	{
		// room not found
		return NULL;
	}
	return &map.find(ptr)->second;
}

/***********************************************************************************
Function: clear
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: resets data to default values
Arguments:	none
************************************************************************************/
void Scene::clear()
{
	rooms.clear();
	name = "";
	order = 0;
	map.clear();
}

/***********************************************************************************
Function: showMap
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: outputs coordinates of rooms in scene (used for debugging)
Arguments:	none
************************************************************************************/
void Scene::showMap()
{
	cout << "Scene: " << name << endl;
	for (std::map<Room*, Coordinate>::iterator it = map.begin(); it != map.end(); it++)
	{
		// for each room in map, display it
		cout << it->first->getName() << "  |  " << it->second.getX() << ", " << it->second.getY() << endl;
	}
}

/***********************************************************************************
Function: setOrder
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: sets the order of the scene in the game
Arguments:	(I/P) int order - order of the scene
************************************************************************************/
void Scene::setOrder(int order)
{
	this->order = order;
}

/***********************************************************************************
Function: getOrder
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: returns order of scene in game
Arguments:	(O/P) int - order of scene
************************************************************************************/
int Scene::getOrder()
{
	return order;
}
