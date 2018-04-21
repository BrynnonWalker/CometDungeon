/***********************************************************************************
File Name: Coordinate.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Coordinate - object that stores the room coordinates for the scene map
Procedures: Coordinate() - default constructor
			Coordinate(int x, int y) - constructor with coordinates
			~Coordinate() - destructor 
			int getX() - returns x coordinate
			int getY() - returns y coordinate
			void down(int val) - subtract val from y
			void up(int val) - add val to y
			void left(int val) - subtract val from x
			void right(int val) - add val to x
************************************************************************************/
#pragma once

class Coordinate
{
private:
	int x, y;	// coordinates
public:
	Coordinate();
	Coordinate(int x, int y);
	~Coordinate();
	int getX();
	int getY();
	void down(int val);
	void up(int val);
	void left(int val);
	void right(int val);
};

