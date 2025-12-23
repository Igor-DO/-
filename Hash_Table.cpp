#include "pch.h"
#include "framework.h"
#include"Token.h"
#include<fstream>
#include "Hash_Table.h"
size_t HashTable::Hash_func(const std::string s) {
		int hash = 5381;
		for (auto c : s) {
			hash = (hash * 33 + c) % SIZE;
		}
		return hash;
	}
HashTable::HashTable() { Table.resize(SIZE); };
int HashTable::enlarge(int n) {
	int a = 2 * n + 1;
	while (1) {
		bool f = 0;
		for (int i = 2; i * i <= a; ++i) {
			if (a % i == 0) {
				f = 1;
				break;
			}
		}
		if (f == 0) {
			return a;
		}
		++a;
	}
}
void HashTable::resize() {
		Deque<Deque<Token>>Temp;
		Temp.resize(SIZE);
		for (int i = 0; i < Table.size(); ++i) {
			for (int j = 0; j < Table[i].size(); ++j) {
				Temp[i].push_back(Table[i][j]);
			}
		}
		for (int i = 0; i < Table.size(); ++i) {
			int t = Table[i].size();
			for (int j = 0; j < t; ++j) {
				Table[i].pop_back();
			}
			Table.pop_front();
		}
		for (int i = Table.size(); i < SIZE; ++i) {
			Deque<Token>D;
			Table.push_back(D);
		}
		for (int i = 0; i < Temp.size(); ++i) {
			for (int j = 0; j < Temp[i].size(); ++j) {
				if (Temp[i][j].line != "") {
					size_t R = Hash_func(Temp[i][j].line);
					Table[R].push_back(Temp[i][j]);
				}
			}
		}
	}
void HashTable::insert(const Token& tok) {
		if (count == SIZE) {
			SIZE = enlarge(SIZE);
			resize();
		}
		size_t ind = Hash_func(tok.line);
		bool f = 0;
		for (int i = 0; i < Table[ind].size(); ++i) {
			if (Table[ind][i].line == tok.line) {
				f = 1;
				break;
			}
		}
		if (f == 0) {
			Table[ind].push_back(tok);
			++count;
		}
	}
void HashTable::print() {
	std::ofstream out("lexer.txt");
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < Table[i].size(); ++j) {
			if(Table[i][j].value()=="ERROR")out << "Error line: "<<Table[i][j].line << "\n";
		}
	}
	out << "HASH TABLE:\n";
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < Table[i].size(); ++j) {
			if (Table[i][j].value() != "ERROR")out << Table[i][j].value() << " | " << Table[i][j].line << " | " << i << "\n";
		}
	}
}