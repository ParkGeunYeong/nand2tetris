#ifndef PARSER_H
#define PARSER_H
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

class Parser
{
private:
	ifstream* input;
	string instruction;
public:
	Parser(ifstream* input);
	bool hasMoreCommands();
	void advance();
	int commandType();
	string symbol();
	string dest();
	string comp();
	string jump();
	string getInstruction();
};
#endif