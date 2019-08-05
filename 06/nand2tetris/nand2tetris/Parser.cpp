#include "Parser.h"

#define A_COMMAND 0
#define C_COMMAND 1
#define L_COMMAND 2

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
	if (instruction[0] == '@')
		return A_COMMAND;
	else if (instruction[0] == '(')
		return L_COMMAND;
	else return C_COMMAND;
}

string Parser::symbol()
{
	if (commandType() == A_COMMAND)
		return instruction.substr(1, string::npos);
	else if (commandType() == L_COMMAND)
		return instruction.substr(1, instruction.size() - 2);
	else return "error - not A and L command";
}

string Parser::dest()
{
	if (commandType() == C_COMMAND) {
		int dest = instruction.find('=');
		if (dest == string::npos) return "";
		else return instruction.substr(0, dest);
	}
	else return "error - not C command";
}

string Parser::comp()
{
	if (commandType() == C_COMMAND) {
		int has_dest = instruction.find('=');
		int has_jump = instruction.find(';');
		if (has_dest != string::npos) {
			if (has_jump != string::npos) {
				return instruction.substr(has_dest + 1, has_jump - has_dest - 1);
			}
			else return instruction.substr(has_dest + 1, instruction.size() - has_dest - 1);
		}
		else {
			if (has_jump != string::npos) {
				return instruction.substr(0, has_jump);
			}
			else return instruction;
		}
	}
	else return "error - not C command";
}

string Parser::jump()
{
	if (commandType() == C_COMMAND) {
		int jump = instruction.find(';');
		if (jump == string::npos) return "";
		else return instruction.substr(jump + 1, instruction.size()-jump+1);
	}
	else return "error - not C command";
}

string Parser::getInstruction()
{

	return instruction;
}
