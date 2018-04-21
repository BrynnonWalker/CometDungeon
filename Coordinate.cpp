/***********************************************************************************
File Name: Coordinate.cpp
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

#include "Coordinate.h"


/***********************************************************************************
Function: Coordinate
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Constructs default coordinate object
Arguments:	none
************************************************************************************/
Coordinate::Coordinate()
{
	x = 0;
	y = 0;
}

/***********************************************************************************
Function: Coordinate
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Constructs default coordinate object
Arguments:	(I/P) int x, y - x and y coordinates
************************************************************************************/
Coordinate::Coordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}

/***********************************************************************************
Function: ~Coordinate
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Destructs coordinate object
Arguments:	none
************************************************************************************/
Coordinate::~Coordinate()
{
}

/***********************************************************************************
Function: getX
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets x coordinate
Arguments:	(O/P) int - returns x
************************************************************************************/
int Coordinate::getX()
{
	return x;
}

/***********************************************************************************
Function: getY
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: gets y coordinate
Arguments:	(O/P) int - returns y
************************************************************************************/
int Coordinate::getY()
{
	return y;
}

/***********************************************************************************
Function: down
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: subtracts val from y coordinate
Arguments:	(I/P) int - val
************************************************************************************/
void Coordinate::down(int val)
{
	y-=val;
}

/***********************************************************************************
Function: up
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds val to y coordinate
Arguments:	(I/P) int - val
************************************************************************************/
void Coordinate::up(int val)
{
	y+=val;
}

/***********************************************************************************
Function: left
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: subtracts val from x coordinate
Arguments:	(I/P) int - val
************************************************************************************/
void Coordinate::left(int val)
{
	x-=val;
}
/***********************************************************************************
Function: right
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: adds val to x coordinate
Arguments:	(I/P) int - val
************************************************************************************/
void Coordinate::right(int val)
{
	x+=val;
}
