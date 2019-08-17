#pragma once
#include<iostream>
#include<fstream>
#include<bitset>
#include "Parser.h"
#include "CodeWriter.h"
using namespace std;

#define C_ARITHMETIC 0
#define C_PUSH 1
#define C_POP 2
#define C_LABEL 3
#define C_GOTO 4
#define C_IF 5
#define C_FUNCTION 6
#define C_RETURN 7
#define C_CALL 8

int main() {
	string filename = "StaticTest";
	string filepath = "MemoryAccess";
	string loc = "C:\\Users\\pgy\\Desktop\\nand2tetris\\projects\\nand2tetris\\07\\";
	ifstream input(loc + filepath + "\\" + filename + "\\" + filename + ".vm");
	Parser parser(&input);
	ofstream output;
	CodeWriter codeWriter(&output);
	codeWriter.setPath("C:\\Users\\pgy\\Desktop\\nand2tetris\\projects\\nand2tetris\\07\\" + filepath + "\\" + filename);
	codeWriter.setFileName(filename);

	if (parser.hasMoreCommands()) {
		parser.advance();
		do {
			if (parser.commandType() == 0) {
				codeWriter.writerArithmetic(parser.arg1());
			}
			else if (parser.commandType() == 1) {
				codeWriter.writePushPop(C_PUSH, parser.arg1(), parser.arg2());
			}
			else if (parser.commandType() == 2) {
				codeWriter.writePushPop(C_POP, parser.arg1(), parser.arg2());
			}
			parser.advance();
		} while (parser.hasMoreCommands());
	}

	codeWriter.close();
	return 0;
}