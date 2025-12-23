#include "pch.h"
#include "framework.h" 
#include "Lexical.h"
#include "Hash_Table.h"
#include "Token.h"
#include <fstream>
#include<string>
Token Lexical::Make_Token(const std::string s,int LINE) {
		Token tok;
		tok.line = s;
		tok.stitch = LINE;
		if (s == "INTEGER")tok.token = Token_Type::INTEGER;
		else if (s == "REAL")tok.token = Token_Type::REAL;
		else if (s == "Const")tok.token = Token_Type::CONST;
		else if (s == "ITOR")tok.token = Token_Type::ITOR;
		else if (s == "RTOI")tok.token = Token_Type::RTOI;
		else if (s == "=")tok.token = Token_Type::ASSIGN;
		else if (s == "+")tok.token = Token_Type::PLUS;
		else if (s == "-")tok.token = Token_Type::MINUS;
		else if (s == "PROGRAM")tok.token = Token_Type::PROGRAM;
		else if (s == "END")tok.token = Token_Type::END;
		else if (s == ")")tok.token = Token_Type::RBRACKET;
		else if (s == "(")tok.token = Token_Type::LBRACKET;
		else if (s == ",")tok.token = Token_Type::PUNCTUATOR;
		else {
			bool number = 0, word = 0, real = 0, wrong = 0;
			for (int i = 0; i < s.size(); ++i) {
				if (s[i] >= '0' && s[i] <= '9')number = 1;
				else if (s[i] >= 'a' && s[i] <= 'z')word = 1;
				else if (s[i] >= 'A' && s[i] <= 'Z')word = 1;
				else if (s[i] == '.')real = 1;
				else wrong = 1;
			}
			if ((number && real==0)&& (s[0] == '0' && s.size() != 1)) {
				tok.token = Token_Type::ERROR;
			}
			else if (number && (!word) && (!wrong) && (!real))tok.token = Token_Type::INTEGER_NUM;
			else if ((!number) && (word) && (!wrong) && (!real))tok.token = Token_Type::ID;
			else if ((!number) && (!word) && (wrong) && (!real))tok.token = Token_Type::ERROR;
			else if ((number) && (!word) && (!wrong) && (real))tok.token = Token_Type::REAL_NUM;
			else tok.token = Token_Type::ERROR;
		}
		return tok;
	}
void Lexical::read(){
	    
		std::string s;
		while (getline(in,s)) {
			++LINE;
			int ind = 0;
			for (int i = 0; i < s.size(); ++i) {
				if (s[i] == ' ') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
				}
				if (s[i] == '\t') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
				}
				if (s[i] == ',') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
					tok = Make_Token(",", LINE);
					TOK.push_back(tok);
					Table.insert(tok);
				}
				if (s[i] == '(') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
					tok = Make_Token("(", LINE);
					TOK.push_back(tok);
					Table.insert(tok);
				}
				if (s[i] == ')') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
					tok = Make_Token(")", LINE);
					TOK.push_back(tok);
					Table.insert(tok);
				}
				if (s[i] == '=') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
					tok = Make_Token("=", LINE);
					TOK.push_back(tok);
					Table.insert(tok);
				}
				if (s[i] == '+') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
					tok = Make_Token("+", LINE);
					TOK.push_back(tok);
					Table.insert(tok);
				}
				if (s[i] == '-') {
					Token tok = Make_Token(s.substr(ind, i - ind), LINE);
					ind = i + 1;
					if (tok.line != "") { Table.insert(tok); TOK.push_back(tok); }
					tok = Make_Token("-", LINE);
					TOK.push_back(tok);
					Table.insert(tok);
				}
				
				if (i == s.size() - 1 && s.substr(ind, i - ind + 1) != "") {
					Token tok = Make_Token(s.substr(ind, i - ind + 1), LINE);
					TOK.push_back(tok);
					Last = tok;
					Table.insert(tok);
				}
			}
		}
	}
void Lexical::write() {
	Table.print();
}
Token Lexical::NextToken() {
	++Number;
	return TOK[Number];

}
Token Lexical::LastTok() {
	return Last;
}
int Lexical::TokCount() {
	return TOK.size();
}
Deque<Token> Lexical::TokenArr() {
	return TOK;
}
int Lexical::TokPos() {
	return Number;
}
void Lexical::insert(Token tok) {
	Table.insert(tok);
}