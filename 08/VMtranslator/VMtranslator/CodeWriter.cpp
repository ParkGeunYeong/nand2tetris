#include "CodeWriter.h"

#define C_ARITHMETIC 0
#define C_PUSH 1
#define C_POP 2
#define C_LABEL 3
#define C_GOTO 4
#define C_IF 5
#define C_FUNCTION 6
#define C_RETURN 7
#define C_CALL 8

string CodeWriter::compare_AB(string cond)
{
	string jcond;
	if (cond == "eq") jcond = "JEQ";
	else if (cond == "gt") jcond = "JGT";
	else if (cond == "lt") jcond = "JLT";
	return "D=M-D\n@J" + tscc(0) + "\nD;"+jcond+"\n@J"
		+ tscc(1) + "\nD;JNE\n(J"
		+ tscc(0) + ")\nD=-1\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(1) + ")\nD=0\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(2) + ")\n";
}

string CodeWriter::compare_eq()
{
	return "D=M-D\n@J" + tscc(0) + "\nD;JEQ\n@J"
		+ tscc(1) + "\nD;JNE\n(J"
		+ tscc(0) + ")\nD=-1\n@J" + tscc(2) +"\n0;JMP\n(J"
		+ tscc(1) + ")\nD=0\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(2) + ")\n";
}

string CodeWriter::compare_gt()
{
	return "D=M-D\n@J" + tscc(0) + "\nD;JGT\n@J"
		+ tscc(1) + "\nD;JLE\n(J"
		+ tscc(0) + ")\nD=-1\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(1) + ")\nD=0\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(2) + ")\n";
}

string CodeWriter::compare_lt()
{
	return "D=M-D\n@J" + tscc(0) + "\nD;JLT\n@J"
		+ tscc(1) + "\nD;JGE\n(J"
		+ tscc(0) + ")\nD=-1\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(1) + ")\nD=0\n@J" + tscc(2) + "\n0;JMP\n(J"
		+ tscc(2) + ")\n";
}

string CodeWriter::tscc(int n)
{
	return to_string(compare_count + n);
}

string CodeWriter::find_index(int index)
{
	string ret = "D=M\n@R13\nM=D\n";
	while (index--) {
		ret += "M=M+1\n";
	}
	return ret;
}

CodeWriter::CodeWriter(ofstream* output)
{
	this->output = output;
}

void CodeWriter::setFileName(string filename)
{
	this->filename = filename;
	this->path_to_vm = path_to_dir + "\\" + filename + ".asm";
	output->open(this->path_to_vm);
}

void CodeWriter::setPath(string path_to_dir)
{
	this->path_to_dir = path_to_dir;
}

void CodeWriter::writerArithmetic(string command)
{
	if (command == "add") {
		text_asm += stack_popAB + "D=M+D\n" + stack_add;
	}
	else if (command == "sub") {
		text_asm += stack_popAB + "D=M-D\n" + stack_add;
	}
	else if (command == "neg") {
		text_asm += stack_popA + "D=-D\n" + stack_add;
	}
	else if (command == "eq") {
		text_asm += stack_popAB + compare_eq() + stack_add;
		compare_count += 3;
	}
	else if (command == "gt") {
		text_asm += stack_popAB + compare_gt() + stack_add;
		compare_count += 3;
	}
	else if (command == "lt") {
		text_asm += stack_popAB + compare_lt() + stack_add;
		compare_count += 3;
	}
	else if (command == "and") {
		text_asm += stack_popAB + "D=D&M\n" + stack_add;
	}
	else if (command == "or") {
		text_asm += stack_popAB + "D=D|M\n" + stack_add;
	}
	else if (command == "not") {
		text_asm += stack_popA + "D=!D\n" + stack_add;
	}
}

void CodeWriter::writePushPop(int command, string segment, int index)
{
	if (command == C_PUSH) {
		if (segment == "constant") {
			text_asm += "@" + to_string(index) + "\nD=A\n" + stack_add;
			//cout << text_asm;
		}
		else if (segment == "local") {
			text_asm += "@LCL\n" + find_index(index) + "@R13\nA=M\nD=M\n" + stack_add;
		}
		else if (segment == "argument") {
			text_asm += "@ARG\n" + find_index(index) + "@R13\nA=M\nD=M\n" + stack_add;
		}
		else if (segment == "this") {
			text_asm += "@THIS\n" + find_index(index) + "@R13\nA=M\nD=M\n" + stack_add;
		}
		else if (segment == "that") {
			text_asm += "@THAT\n" + find_index(index) + "@R13\nA=M\nD=M\n" + stack_add;
		}
		else if (segment == "temp") {
			text_asm += "@R"+ to_string(5+index) + "\nD=M\n" + stack_add;
		}
		else if (segment == "pointer") {
			if (index == 0) text_asm += "@THIS\nD=M\n" + stack_add;
			else text_asm += "@THAT\nD=M\n" + stack_add;
		}
		else if (segment == "static") {
			text_asm += "@" + filename + "." + to_string(index) + "\nD=M\n" + stack_add;
		}
	}
	else if (command == C_POP) {
		string mid;
		if (segment == "local") {
			text_asm += "@LCL\n" + find_index(index) + stack_popA + "@R13\nA=M\nM=D\n";
		}
		else if (segment == "argument") {
			text_asm += "@ARG\n" + find_index(index) + stack_popA + "@R13\nA=M\nM=D\n";
		}
		else if (segment == "this") {
			text_asm += "@THIS\n" + find_index(index) + stack_popA + "@R13\nA=M\nM=D\n";
		}
		else if (segment == "that") {
			text_asm += "@THAT\n" + find_index(index) + stack_popA + "@R13\nA=M\nM=D\n";
		}
		else if (segment == "temp") {
			text_asm += stack_popA + "@R" + to_string(5 + index) + "\nM=D\n";
		}
		else if (segment == "pointer") {
			if (index == 0) text_asm += stack_popA + "@THIS\nM=D\n";
			else text_asm += stack_popA + "@THAT\nM=D\n";
		}
		else if (segment == "static") {
			text_asm += stack_popA + "@" + filename + "." + to_string(index) + "\nM=D\n";
		}
	}
}

void CodeWriter::writerInint()
{
}

void CodeWriter::writeLabel(string label)
{
	text_asm += "(" + label + ")\n";
}

void CodeWriter::writeGoto(string label)
{
	text_asm += "@" + label + "\n0;JMP\n";
}

void CodeWriter::writeIf(string label)
{
	text_asm += stack_popA + "@" + label + "\nD;JNE\n";
}

void CodeWriter::writeCall(string functionName, int numArgs)
{
	text_asm += "@return-address\nD=A\n" + stack_add;
	text_asm += "@LCL\nD=M\n" + stack_add;
	text_asm += "@ARG\nD=M\n" + stack_add;
	text_asm += "@THIS\nD=M\n" + stack_add;
	text_asm += "@THAT\nD=M\n" + stack_add;
	text_asm += "@SP\nD=M\n";
	numArgs += 5;
	while(numArgs--) text_asm += "D=D-1\n";
	text_asm += "@ARG\nM=D\n";
	text_asm += "@SP\nD=M\n";
	text_asm += "@LCL\nM=D\n";
	writeGoto(functionName);
	writeLabel("return-address");
}

void CodeWriter::writeReturn()
{
	text_asm += "@LCL\nD=M\n@R14\nM=D\nD=M-1\nD=D-1\nD=D-1\nD=D-1\nD=D-1\nA=D\nD=M\n@R15\nM=D\n";
	text_asm += stack_popA + "@ARG\nA=M\nM=D\nD=A+1\n@SP\nM=D\n";
	text_asm += "@R14\nD=M-1\nA=D\nD=M\n@THAT\nM=D\n";
	text_asm += "@R14\nD=M-1\nD=D-1\nA=D\nD=M\n@THIS\nM=D\n";
	text_asm += "@R14\nD=M-1\nD=D-1\nD=D-1\nA=D\nD=M\n@ARG\nM=D\n";
	text_asm += "@R14\nD=M-1\nD=D-1\nD=D-1\nD=D-1\nA=D\nD=M\n@LCL\nM=D\n";
	text_asm += "@R15\nA=M\n0;JMP\n";
}

void CodeWriter::writeFunction(string functionName, int numLocals)
{
	writeLabel(functionName);
	while(numLocals--) writePushPop(C_PUSH, "constant", 0);
}

void CodeWriter::close()
{
	cout << text_asm;
	*output << text_asm.substr(0, text_asm.size() - 1);
	output->close();
}
