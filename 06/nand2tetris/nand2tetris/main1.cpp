//기호를 처리하지 않는 어셈블러 @10진수, (10진수)
#pragma once
#include<iostream>
#include<fstream>
#include<bitset>
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"
using namespace std;

#define A_COMMAND 0
#define C_COMMAND 1
#define L_COMMAND 2

bool is_digit(string str) {
	return atoi(str.c_str()) != 0 || str.compare("0") == 0;
}

int main() {
	string loc1 = "pong", loc2 = "Pong";
	ifstream input1("C:\\Users\\pgy\\Desktop\\nand2tetris\\projects\\nand2tetris\\06\\" + loc1 + "\\" + loc2 + ".asm");
	ifstream input2("C:\\Users\\pgy\\Desktop\\nand2tetris\\projects\\nand2tetris\\06\\" + loc1 + "\\" + loc2 + ".asm");
	ofstream output("C:\\Users\\pgy\\Desktop\\nand2tetris\\projects\\nand2tetris\\06\\" + loc1 + "\\" + loc2 + ".hack");
	Parser parser1(&input1);
	Parser parser2(&input2);
	SymbolTable symbolTable;

	int romAddress = 0;
	if (parser1.hasMoreCommands()) {
		parser1.advance();
		do {
			int commandType = parser1.commandType();
			if (commandType == L_COMMAND) {
				string lSymbol = parser1.symbol();
				if (!is_digit(lSymbol)) {
					symbolTable.addEntry(lSymbol, romAddress);
					//cout << symbolTable.getAddress(lSymbol) << "--";
				}
			}
			else romAddress++;
			//cout << parser1.getInstruction() << '\n';
			parser1.advance();
		} while (parser1.hasMoreCommands());
	}

	int ramAddress = 16;
	string makeHackFile = "";
	if (parser2.hasMoreCommands()) {
		parser2.advance();
		do {
			int commandType = parser2.commandType();
			if (commandType == A_COMMAND) {
				string aSymbol = parser2.symbol();
				int aSymbolToAddress;
				if (!is_digit(aSymbol)) {
					if (symbolTable.contains(aSymbol))
						aSymbolToAddress = symbolTable.getAddress(aSymbol);
					else {
						symbolTable.addEntry(aSymbol, ramAddress);
						aSymbolToAddress = ramAddress;
						ramAddress++;
					}
				}
				else 
					aSymbolToAddress = stoi(aSymbol);
				bitset<16> a_bitset(aSymbolToAddress);
				makeHackFile += a_bitset.to_string() + '\n';
			}
			else if (commandType == C_COMMAND) {
				string c = "111";
				c += Code::comp(parser2.comp());
				c += Code::dest(parser2.dest());
				c += Code::jump(parser2.jump());
				makeHackFile += c + '\n';
			}
			//cout << parser2.getInstruction() << '\n';
			parser2.advance();
		} while (parser2.hasMoreCommands());
	}
	//cout << makeHackFile;
	output << makeHackFile.substr(0, makeHackFile.size() - 1);

	return 0;
}