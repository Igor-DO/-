#pragma once
#include<string>
enum Token_Type {
	KEYWORD, PLUS,  MINUS, PROGRAM, END, INTEGER, INTEGER_NUM, REAL,REAL_NUM, PUNCTUATOR, ERROR, ITOR,RTOI, ID,LBRACKET,RBRACKET,CONST, ASSIGN
};
struct Token {
	std::string line;
	Token_Type token;
	std::string value();
	int stitch;
};