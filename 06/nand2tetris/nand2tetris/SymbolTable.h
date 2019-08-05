#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include<iostream>
#include<unordered_map>
using namespace std;

class SymbolTable
{
private:
	unordered_map<string, int> symbolTable;
public:
	SymbolTable();
	void addEntry(string symbol, int address);
	bool contains(string symbol);
	int getAddress(string symbol);
};

#endif