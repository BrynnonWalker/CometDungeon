/***********************************************************************************
File Name: Pathway.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Pathway - paths between rooms
Procedures:		Pathway() - constructor
				~Pathway() - destructor
				string getName() - gets path nae
				void setName(string name) - sets path name
				void setDesc(string descr) - sets path description
				string getExit() - gets exit
				void setRoom(string exit) - sets connecting room
				void setDirection(string dir) - sets current direction
				string getDirection() - gets current direction
				void clear() - resets paths to default
				bool isConnected() - checks if room is connected
				void connect(string room) - connects two rooms
				void display() - displays paths
				void close() - close a path
************************************************************************************/

#pragma once

#include <string>

using namespace std;

class Pathway
{
private:
	string name;			// name of room
	string exit;			// connected room
	string description;
	string direction;		// direction path points in
	bool connected;
public:
	Pathway();
	~Pathway();
	string getName();
	void setName(string name);
	void setDesc(string descr);
	string getExit();
	void setRoom(string exit);
	void setDirection(string dir);
	string getDirection();
	void clear();
	bool isConnected();
	void connect(string room);
	void display();
	void close();
};

