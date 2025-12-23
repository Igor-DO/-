#include "pch.h"
#include "framework.h"
#include<string>
#include"Token.h"
#include"Hash_Table.h"
#include"Tree.h"
using namespace std;
void Tree::add(Tree* child) {
	Children.push_back(child);
}
