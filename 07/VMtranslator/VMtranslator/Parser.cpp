#include "Parser.h"

#define C_ARITHMETIC 0
#define C_PUSH 1
#define C_POP 2
#define C_LABEL 3
#define C_GOTO 4
#define C_IF 5
#define C_FUNCTION 6
#define C_RETURN 7
#define C_CALL 8

Parser::Parser(ifstream * input)
{
	this->input = input;
}

bool Parser::hasMoreCommands()
{
	if (*input) return true;
	else return false;
}

void Parser::advance()
{
	getline(*input, instruction);
	instruction.erase(remove_if(instruction.begin(), instruction.end(), isspace), instruction.end());
	int commentLocation = instruction.find("//");
	if (commentLocation != string::npos) instruction = instruction.substr(0, commentLocation);
	if (hasMoreCommands() && (instruction.substr(0, 2) == "//" || instruction.empty()))
		advance();
}

int Parser::commandType()
{
	for (string ct : commandTypes) if (instruction == ct) return C_ARITHMETIC;
	if (instruction.substr(0, 3) == "pop") return C_POP;
	if (instruction.substr(0, 4) == "push") return C_PUSH;
}

string Parser::arg1()
{
	if (commandType() == C_ARITHMETIC) return instruction;
	if (commandType() == C_POP) for (string s : segments) if (instruction.substr(3, s.size()) == s) return s;
	if (commandType() == C_PUSH) for (string s : segments) if (instruction.substr(4, s.size()) == s) return s;
}

int Parser::arg2()
{
	if (commandType() == C_POP) return stoi(instruction.substr(3 + arg1().size(), string::npos));
	if (commandType() == C_PUSH) return stoi(instruction.substr(4 + arg1().size(), string::npos));
}

string Parser::getInstruction()
{
	return instruction;
}
