#include "Code.h"

string Code::dest(string dest)
{
	string binary_dest;
	if (dest.find('A') != string::npos)binary_dest += '1';
	else binary_dest += '0';
	if (dest.find('D') != string::npos)binary_dest += '1';
	else binary_dest += '0';
	if (dest.find('M') != string::npos)binary_dest += '1';
	else binary_dest += '0';
	return binary_dest;
}

string Code::comp(string comp)
{
	if (comp == "0") return "0101010";
	else if (comp == "1") return "0111111";
	else if (comp == "-1") return "0111010";
	else if (comp == "D") return "0001100";
	else if (comp == "A") return "0110000";
	else if (comp == "!D") return "0001101";
	else if (comp == "!A") return "0110001";

	else if (comp == "-D") return "0001111";
	else if (comp == "-A") return "0110011";
	else if (comp == "D+1" || comp == "1+D") return "0011111";
	else if (comp == "A+1" || comp == "1+A") return "0110111";
	else if (comp == "D-1") return "0001110";
	else if (comp == "A-1") return "0110010";
	else if (comp == "D+A" || comp == "A+D") return "0000010";

	else if (comp == "D-A") return "0010011";
	else if (comp == "A-D") return "0000111";
	else if (comp == "D&A" || comp == "A&D") return "0000000";
	else if (comp == "D|A" || comp == "A|D") return "0010101";
	else if (comp == "M") return "1110000";
	else if (comp == "!M") return "1110001";
	else if (comp == "-M") return "1110011";

	else if (comp == "M+1" || comp == "1+M") return "1110111";
	else if (comp == "M-1") return "1110010";
	else if (comp == "D+M" || comp == "M+D") return "1000010";
	else if (comp == "D-M") return "1010011";
	else if (comp == "M-D") return "1000111";
	else if (comp == "D&M" || comp == "M&D") return "1000000";
	else if (comp == "D|M" || comp == "M|D") return "1010101";
}

string Code::jump(string jump)
{
	if (jump.empty()) return "000";
	else if (jump == "JGT") return "001";
	else if (jump == "JEQ") return "010";
	else if (jump == "JGE") return "011";
	else if (jump == "JLT") return "100";
	else if (jump == "JNE") return "101";
	else if (jump == "JLE") return "110";
	else if (jump == "JMP") return "111";
}

