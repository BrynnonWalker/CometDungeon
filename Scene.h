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
			bool addMultiRoom(Room room, int num) - adds room to scene room list based on input value
			string getRoomFilename() - returns scene name
			int getNumRooms() - returns number of rooms in scene
			Room* getRoom(int numRoom) - returns room at input location in rooms vector
			Coordinate* getRoomCoordinate(string roomName) - returns coordinate of room
			void clear() - resets room to default values
			void showMap() - displays the coordinates of rooms (used for debugging)
			void setOrder(int order) - sets order of scene
			int getOrder() - returns order of scene
************************************************************************************/
#pragma once

#include "Room.h"
#include "Coordinate.h"

#include <vector>
#include <map>
#include <string>

using namespace std;
class Scene
{
private:
	vector<Room> rooms; // list of rooms in scene
	string name;	// name of scene
	int order;		// order in which this scene connects to others
	std::map<Room*, Coordinate> map;	// map of scene
	Room* getRoom(string roomName);
	void fixMapPathing(Room* roomPtr);
	void displayLevel(int level, int current, int end, Room* currentRoom);
public:
	Scene();
	~Scene();
	void displayMap(Room* currentRoom);
	bool buildMap();
	void setName(string str); // set scene name
	bool addRoom(Room room);  // adds room to scene's room list
	bool addMultiRoom(Room room, int num);
	string getRoomFilename(); // returns scene name
	int getNumRooms();
	Room* getRoom(int numRoom);
	Coordinate* getRoomCoordinate(string roomName);
	void clear();
	void showMap();
	void setOrder(int order);
	int getOrder();
};

