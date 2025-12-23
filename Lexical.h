#pragma once
#include "Hash_Table.h"
#include "Token.h"
#include<fstream>
#include<string>
class Lexical {
	HashTable Table;
	std::ifstream in;
	Deque<Token>TOK;
	int Number = -1;
	Token Last;
public:
	int LINE = 0;
	Lexical() {
		in.open("input.txt");
	};
	void insert(Token tok);
	Token Make_Token(const std::string s,int LINE);
	void read();
	void write();
	int TokCount();
	int TokPos();
	Token LastTok();
	Deque<Token> TokenArr();
	Token NextToken();
	~Lexical() = default;
};