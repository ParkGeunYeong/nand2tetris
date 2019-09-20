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
	getline(*input, instructionTemp);
	int commentLocation = instructionTemp.find("//");
	if (commentLocation != string::npos) instructionTemp = instructionTemp.substr(0, commentLocation);
	if (hasMoreCommands() && (instructionTemp.substr(0, 2) == "//" || instructionTemp.empty()))
		advance();

	stringstream instructions(instructionTemp);
	string temp;
	int i = 0;
	while (instructions >> temp) {
		instruction[i] = temp; i++;
	}
	
	//instruction.erase(remove_if(instruction.begin(), instruction.end(), isspace), instruction.end());
	
}

int Parser::commandType()
{
	for (string ct : commandTypes) if (instruction[0] == ct) return C_ARITHMETIC;
	if (instruction[0] == "pop") return C_POP;
	if (instruction[0] == "push") return C_PUSH;
	if (instruction[0] == "label") return C_LABEL;
	if (instruction[0] == "goto") return C_GOTO;
	if (instruction[0] == "if-goto") return C_IF;
	if (instruction[0] == "function") return C_FUNCTION;
	if (instruction[0] == "return") return C_RETURN;
	if (instruction[0] == "call") return C_CALL;
}

string Parser::arg1()
{
	if (commandType() == C_ARITHMETIC) return instruction[0];
	if (commandType() == C_POP) for (string s : segments) if (instruction[1] == s) return s;
	if (commandType() == C_PUSH) for (string s : segments) if (instruction[1] == s) return s;
	if (commandType() == C_LABEL) return instruction[1];
	if (commandType() == C_GOTO || commandType() == C_IF || commandType() == C_FUNCTION || commandType() == C_CALL)
		return instruction[1];
}

int Parser::arg2()
{
	if (commandType() == C_POP || commandType() == C_PUSH || commandType() == C_FUNCTION || commandType() == C_CALL)
		return stoi(instruction[2]);
}

string Parser::getInstruction()
{
	return instructionTemp;
}
