#include "pch.h"
#include "framework.h"
#include<string>
#include "Token.h"
std::string Token::value() {
	std::string s;
	if (token == PROGRAM)s = "PROGRAM";
	if (token == END)s = "END";
	if (token == INTEGER)s = "INTEGER";
	if (token == REAL)s = "REAL";
	if (token == INTEGER_NUM)s = "INTEGER_NUM";
	if (token == REAL_NUM)s = "REAL_NUM";
	if (token == ID)s = "ID";
	if (token == PLUS)s = "PLUS";
	if (token == MINUS)s = "MINUS";
	if (token == ERROR)s = "ERROR";
	if (token == PUNCTUATOR)s = "PUNCTUATION";
	if (token == CONST)s = "CONST";
	if (token == RTOI)s = "RTOI";
	if (token == ITOR)s = "ITOR";
	if (token == KEYWORD)s = "KEYWORD";
	if (token == LBRACKET)s = "LBRACKET";//
	if (token == RBRACKET)s = "RBRACKET";
	if (token == ASSIGN)s = "ASSIGN";
	return s;
}