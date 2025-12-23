#include "pch.h"
#include "framework.h"
#include<iostream>
#include<iterator>
#include<string>
#include<fstream>
#include"Lexical.h"
#include"Tree.h"
#include"Sintax.h"
using namespace std;
Sintax::Sintax() {
	out.open("output.txt");
	lexer.read();
	lexer.write();
	token = lexer.NextToken();
}
void Sintax::Error_Message() {
	if (ErrorCount == 0) {
		if (token.stitch > 0)out << "Error: line " << token.stitch << "\n";
		else out << "Error: last line\n";
		++ErrorCount;
		err = token;
	}
}
Deque<Token> Sintax::TakeLex() {
	return lexer.TokenArr();
}
Tree* Sintax::Program() {
	Tree* node = new Tree("Program");
	node->add(Begin());
	node->add(Descriptions());
	node->add(Operators());
	node->add(End());
	return node;
}
Tree* Sintax::Begin() {
	Tree* node = new Tree("Begin");
	if (token.token == Token_Type::PROGRAM) {
		node->add(new Tree("PROGRAM", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		node->add(Id());
	}
	else Error_Message();
	return node;
}
Token Sintax::LastTok() {
	return lexer.LastTok();
}
Tree* Sintax::End() {
	Tree* node = new Tree("End");
	if (token.token == Token_Type::END) {
		node->add(new Tree("END", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		node->add(Id());
	}
	else Error_Message();
	return node;
}
Tree* Sintax::Descriptions() {
	Tree* node = new Tree("Descriptions");
	while (token.token == Token_Type::INTEGER || token.token == Token_Type::REAL) {
		node->add(Descr());
	}
	return node;

}
Tree* Sintax::Operators() {
	Tree* node = new Tree("Operators");
	while (token.token == Token_Type::ID) {

		node->add(Op());
	}
	return node;
}
Tree* Sintax::Expr() {
	Tree* node = new Tree("Expr");
	node->add(SimpleExpr());
	if (token.token == Token_Type::PLUS) {
		node->add(new Tree("PLUS", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		node->add(Expr());
	}
	else if (token.token == Token_Type::MINUS) {
		node->add(new Tree("MINUS", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		node->add(Expr());
	}
	return node;
}
Tree* Sintax::Id() {
	if (token.token == Token_Type::ID) {
		Tree* node = new Tree("Id", token);
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		return node;
	}
	else {
		Error_Message(); return nullptr;
	}
}
Tree* Sintax::Op() {
	Tree* node = new Tree("Op");
	if (token.token == Token_Type::ID) {
		node->add(new Tree("Id", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else {
			Error_Message(); return node;
		}
		if (token.token == Token_Type::ASSIGN) {
			node->add(new Tree("Assign", token));
			if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
			else {
				Error_Message(); return node;
			}
			node->add(Expr());
		}
		else Error_Message();
	}
	else Error_Message();
	return node;
}
Tree* Sintax::Descr() {
	Tree* node = new Tree("Descr");
	node->add(Type());
	node->add(VarList());
	return node;
}
Tree* Sintax::Type() {
	Tree* node = new Tree("Type");
	if (token.token == Token_Type::INTEGER) {
		node->add(new Tree("INTEGER", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
	}
	else if (token.token == Token_Type::REAL) {
		node->add(new Tree("REAL", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
	}
	else Error_Message();
	return node;
}
Tree* Sintax::VarList() {
	Tree* node = new Tree("VarList");
	node->add(Id());
	while (token.token == Token_Type::PUNCTUATOR) {
		node->add(new Tree("PUNCTUATOR", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else {
			Error_Message(); return node;
		}
		node->add(Id());
	}
	return node;
}
Tree* Sintax::SimpleExpr() {
	Tree* node = new Tree("SimpleExpr");
	if (token.token == Token_Type::ID) {
		node->add(Id());
	}
	else if (token.token == Token_Type::CONST) {
		node->add(Const());
	}
	else if (token.token == Token_Type::INTEGER_NUM) {
		node->add(new Tree("INTEGER_NUM", token));
		if (lexer.TokPos() != lexer.TokCount()) token = lexer.NextToken();
		else Error_Message();
	}
	else if (token.token == Token_Type::REAL_NUM) {
		node->add(new Tree("REAL_NUM", token));
		if (lexer.TokPos() != lexer.TokCount()) token = lexer.NextToken();
		else Error_Message();
	}
	else if (token.token == Token_Type::ITOR) {
		node->add(new Tree("ITOR", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		if (token.token == Token_Type::LBRACKET) {
			node->add(new Tree("LBRACKET", token));
			if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
			else Error_Message();
			node->add(Expr());
			if (token.token == Token_Type::RBRACKET) {
				node->add(new Tree("RBRACKET", token));
				if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
				else Error_Message();
			}
			else Error_Message();
		}
		else Error_Message();
	}
	else if (token.token == Token_Type::RTOI) {
		node->add(new Tree("RTOI", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		if (token.token == Token_Type::LBRACKET) {
			node->add(new Tree("LBRACKET", token));
			if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
			else Error_Message();
			node->add(Expr());
			if (token.token == Token_Type::RBRACKET) {
				node->add(new Tree("RBRACKET", token));
				if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
				else Error_Message();
			}
			else Error_Message();
		}
		else Error_Message();
	}
	else if (token.token == Token_Type::LBRACKET) {
		node->add(new Tree("LBRACKET", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		node->add(Expr());
		node->add(new Tree("RBRACKET", token));
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
	}
	else Error_Message();
	return node;
}
Tree* Sintax::Const() {
	if (token.token == Token_Type::INTEGER_NUM) {
		Tree* node = new Tree("INTEGER_NUM", token);
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		return node;
	}
	else if (token.token == Token_Type::REAL_NUM) {
		Tree* node = new Tree("REAL_NUM", token);
		if (lexer.TokPos() != lexer.TokCount())token = lexer.NextToken();
		else Error_Message();
		return node;
	}
	else Error_Message();
}
bool Sintax::Correct() {
	return ErrorCount;
}
void Sintax::PrintSin(Tree* T, int depth) {

	if (T->name == "")return;
	else {
		for (int i = 0; i < depth; ++i)out << "-";
		out << T->name << " ";
		out << T->token1.line << "\n";
		for (int i = 0; i < T->Children.size(); ++i) {
			PrintSin(T->Children[i], depth + 1);
		}
	}

}
