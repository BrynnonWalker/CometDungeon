/***********************************************************************************
File Name: main.cpp
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: none
Procedures: main() - Initializes game and shows main menu
			displayIntro() - Displays game intro
			string makeLower(string str) - converts a string to lowercase
************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

using namespace std;

void displayIntro();
string makeLower(string str);

/***********************************************************************************
Function: main
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Initializes game and shows main menu
Arguments:	none
************************************************************************************/
int main()
{
	string read = "";
	bool quit = false;
	Game* MyGame = new Game();
	int tries = 5;
	
	while(!MyGame->IsLoaded() && tries > 0)
	{
		delete MyGame; 
		cout << "Reloading game" << endl;
		MyGame = new Game();
		tries--;
	}
	
	if (MyGame->IsLoaded())
	{
		// game data loaded correctly

		displayIntro();

		while (!quit)
		{

			// display game menu
			cout << "a) New Game" << endl
				<< "b) Load Game" << endl
				<< "c) Quit Game" << endl;

			read = "";
			while (read.size() < 1)
			{
				// get input
				getline(cin, read);
			}
			switch (read.at(0))
			{
			case 'A':
			case 'a':
				cout << "New Game selected." << endl;
				cout << "Please enter character name: " << endl;
				cout << "Note that re-using a character name from other save files will overwrite the" << endl
					<< "original file." << endl;
				cout << "If you would not like to start a new game, please enter 'GO BACK'" << endl;

				read = "";

				while (read.size() < 1)
				{
					// get name
					getline(cin, read);
				}

				// make lower case
				read = makeLower(read);

				if (read.compare("go back") != 0)
				{
					// do not go back, create new game
					MyGame->NewGame(read);
					quit = true;
				}

				break;
			case 'B':
			case 'b':
				cout << "Load Game selected." << endl;
				cout << "Please enter character name: " << endl;

				read = "";

				while (read.size() < 1)
				{
					// get name
					getline(cin, read);
				}
				
				// make lower
				read = makeLower(read);

				// check if character file exists
				if (!MyGame->LoadGame(read))
				{
					// game not loaded
					cout << "Save file not found." << endl;
				}
				else
				{
					quit = true;
				}

				break;
			case 'C':
			case 'c':
				cout << "Quitting..." << endl;
				quit = true;
				break;
			default:
				// invalid input
				cout << "Invalid selection." << endl;
				break;
			}
		}
	}

	cout << "Enter a character to continue..." << endl;
	char pause;
	cin >> pause;
	return 0;
}

/***********************************************************************************
Function: displayIntro
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Displays game intro
Arguments:	none
************************************************************************************/
void displayIntro()
{
	cout << "###############" << endl;
	cout << "Comet Dungeon" << endl;
	cout << "Developers: " << endl;
	cout << "Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker" << endl;
	cout << "04/25/2016" << endl;
	cout << "###############" << endl;
}

/***********************************************************************************
Function: makeLower
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Description: Converts a string to lowercase
Arguments:	(I/P) string str - original string
			(O/P) string - converted string
************************************************************************************/
string makeLower(string str)
{
	string temp = "";
	for (size_t i = 0; i < str.length(); i++)
	{
		temp += tolower(str.at(i));
	}

	return temp;
}
