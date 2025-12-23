#pragma once
#include<iostream>
#include<iterator>
#include<string>
#include<fstream>
#include"Lexical.h"
#include"Tree.h"
using namespace std;
class Sintax {
	Lexical lexer;
	Token token;
	int ErrorCount = 0;
	ofstream out;
	Deque<Token> D = lexer.TokenArr();
	Token err;
public:
	Sintax();
	void Error_Message();
	Deque<Token> TakeLex();
	Token LastTok();
	Tree* Program();
	Tree* Begin();
	Tree* End();
	Tree* Descriptions();
	Tree* Operators();
	Tree* Expr();
	Tree* Id();
	Tree* Op();
	Tree* Descr();
	Tree* Type();
	Tree* VarList();
	Tree* SimpleExpr();
	Tree* Const();
	bool Correct();
	void PrintSin(Tree* T, int depth);
};
