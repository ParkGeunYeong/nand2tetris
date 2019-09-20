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
	string filename = "SimpleFunction";
	string filepath = "FunctionCalls";
	string loc = "..\\..\\";
	ifstream input(loc + filepath + "\\" + filename + "\\" + filename + ".vm");
	Parser parser(&input);
	ofstream output;
	CodeWriter codeWriter(&output);
	codeWriter.setPath("..\\..\\" + filepath + "\\" + filename);
	codeWriter.setFileName(filename);

	if (parser.hasMoreCommands()) {
		parser.advance();
		do {
			if (parser.commandType() == 0) {
				codeWriter.writerArithmetic(parser.arg1());
			}
			else if (parser.commandType() == C_PUSH) {
				codeWriter.writePushPop(C_PUSH, parser.arg1(), parser.arg2());
			}
			else if (parser.commandType() == C_POP) {
				codeWriter.writePushPop(C_POP, parser.arg1(), parser.arg2());
			}
			else if (parser.commandType() == C_LABEL) {
				codeWriter.writeLabel(parser.arg1());
			}
			else if (parser.commandType() == C_GOTO) {
				codeWriter.writeGoto(parser.arg1());
			}
			else if (parser.commandType() == C_IF) {
				codeWriter.writeIf(parser.arg1());
			}
			else if (parser.commandType() == C_FUNCTION) {
				codeWriter.writeFunction(parser.arg1(), parser.arg2());
			}
			else if (parser.commandType() == C_RETURN) {
				codeWriter.writeReturn();
			}
			else if (parser.commandType() == C_CALL) {
				codeWriter.writeCall(parser.arg1(), parser.arg2());
			}
			parser.advance();
		} while (parser.hasMoreCommands());
	}

	codeWriter.close();
	return 0;
}