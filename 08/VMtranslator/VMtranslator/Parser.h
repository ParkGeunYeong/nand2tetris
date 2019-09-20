#ifndef PARSER_H
#define PARSER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;

class Parser
{
private:
	ifstream* input;
	string instruction[3], instructionTemp;
	string commandTypes[9] = {
		"add","sub","neg","eq","gt","lt","and","or","not"
	};
	string segments[8] = {
		"argument","local","static","constant","this","that","pointer","temp"
	};
public:
	Parser(ifstream* input);
	bool hasMoreCommands();
	void advance();
	int commandType();
	string arg1();
	int arg2();
	string getInstruction();
};
#endif