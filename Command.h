/***********************************************************************************
File Name: Command.h
Authors: Mavis Francia, Warren Hyman, Ryan Johnson, Praveen Mannava, Brynnon Walker
Classes: Command - base object for all commands
Procedures: void setName(string name) - sets the command name
			void setDesc(string desc) - sets the command description
			void setCmdList(vector<Command*>* cmdList) - sets the command list
			Command() - constructs a command
			~Command() - destructs a command
			void clear() - resets command data
			void resetCallers() - clears the caller list
			void resetReceivers() - clears the receiver list
			void setSplit(bool flag) - sets whether command can have multiple receivers
			bool checkName(string name) - checks if command name matches input
			bool addCmdName(string caller) - add new caller for command
			bool addReceiver(string receiver) - add new receiver for command
			bool checkCommand(string cmd) - checks cmd for appropriate callers and receivers
			string removeCaller(string cmd) - returns the input - caller
			string getCmdName() - returns command name
			string getCmdDesc() - returns command description
			vector<string>* getSplitters() - returns a pointer to splitters vector
			virtual bool action(string cmd, Player* player) = 0 - virtual form of action function (implemented in child classes)
************************************************************************************/
#pragma once

#include "Player.h"

#include <vector>
#include <string>

using namespace std;

class Command
{
private:
	bool allowSplit;
	vector<string> callers;	// list of valid verbs for command to execute
	vector<string> receivers; // list of valid receivers of command		ex: <open> "door"|"chest"|"inventory"|"book"
	vector<string> splitters = { "and", ",", "plus", "as well as", "together with", "along with", "also" }; // list of strings that split command receivers
	string name, description;
protected:
	vector<Command*>* cmdListPtr;
	void setName(string name);
	void setDesc(string desc);
public:
	void setCmdList(vector<Command*>* cmdList);
	Command();
	~Command();
	void clear();
	void resetCallers();
	void resetReceivers();
	void setSplit(bool flag);
	bool checkName(string name);
	bool addCmdName(string caller);
	bool addReceiver(string receiver);
	bool checkCommand(string cmd);
	string removeCaller(string cmd);
	string getCmdName();
	string getCmdDesc();
	vector<string>* getSplitters();
	virtual bool action(string cmd, Player* player) = 0;
};

