#ifndef CODEWRITER_H
#define CODEWRITER_H
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

class CodeWriter
{
private:
	ofstream* output;
	string text_asm;
	string path_to_dir;
	string filename;
	string path_to_vm;
	string stack_add = "@SP\nA=M\nM=D\n@SP\nM=M+1\n";
	string stack_popAB = "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\n";
	string stack_popA = "@SP\nAM=M-1\nD=M\n";
	int compare_count = 0;
	string compare_eq();
	string compare_gt();
	string compare_lt();
	string tscc(int n);
	string find_index(int index);
public:
	CodeWriter(ofstream* output);
	void setFileName(string filename);
	void setPath(string path_to_dir);
	void writerArithmetic(string command);
	void writePushPop(int command, string segment, int index);
	void close();
};
#endif