#pragma once
#include<string>
#include"Token.h"
#include"Hash_Table.h"
using namespace std;
class Tree {
public:
	string name = "";
	Deque<Tree*>Children;
	Token token1;
	Tree(const string str) :name(str) {};
	Tree(const string str, Token tok) :name(str)
	{
		token1.token = tok.token;
		token1.line = tok.line;
		token1.stitch = tok.stitch;
	};
	void add(Tree* child);
	~Tree() = default;
};