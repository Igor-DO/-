#include<iostream>
#include<iterator>
#include<string>
#include<fstream>
#include"Lexical.h"
#include"Tree.h"
#include"Sintax.h"
#include<vector>
#include<set>
#include<stack>
#include<deque>
using namespace std;
ofstream out("out.txt");
struct Data {
	int line;
	string val;
};
class Semantic {
	Sintax sin;
	int Pos = 0;
	int S =0;
	Data D;
	Deque<Token>AllTok;
	Deque<Data>ErrArr;
	Deque<Data>IntArr;
	Deque<Data>RealArr;
	Deque<int>As;
	Deque<string>Post;
	short f = 0;
	string ProgID;
	bool ErrFl = 0;
	
public:
	Semantic() {
		
		Tree* T = sin.Program();
		if (!sin.Correct())
			sin.PrintSin(T, -1);
		ErrFl = (!sin.Correct());
		AllTok = sin.TakeLex();
		AllTok.push_back(sin.LastTok());
		S = AllTok.size();

	}
	void CheckType(int a,int b,bool c) {
		int skob=0,t=a;
		bool ValType=c;
		if (c) {
			while (t <= b) {
				if (AllTok[t].token==Token_Type::REAL_NUM || AllTok[t].token == Token_Type::PLUS ||
					AllTok[t].token == Token_Type::MINUS || AllTok[t].token == Token_Type::LBRACKET || AllTok[t].token == Token_Type::RBRACKET) {
					
				}
				else if (AllTok[t].token == Token_Type::ID) {
					short flag = 0;
					for (int i = 0; i < RealArr.size(); ++i) {
						if (RealArr[i].val == AllTok[t].line) {
							flag = 1;
							break;
						}
					}
					for (int i = 0; i < IntArr.size(); ++i) {
						if (IntArr[i].val == AllTok[t].line) {
							flag = 2;
							break;
						}
					}
					if (flag == 2) {
						Data D;
						D.line = AllTok[t].stitch;
						D.val = "Error: Wrong Type!!!";
						ErrArr.push_back(D);
					}
					if (flag == 0) {
						Data D;
						D.line = AllTok[t].stitch;
						D.val = "Error: ID is not determinated!!!";
						ErrArr.push_back(D);
					}
				}
				else if (AllTok[t].token == Token_Type::ITOR) {
					for (int i = t+1; i <= b; ++i) {
						skob += (AllTok[i].line == "(");
						skob -= (AllTok[i].line == ")");
						if (skob == 0) {
							CheckType(t + 2, i - 1, 0);
							t = i;
							break;
						}
					}
				}
				else {
					Data D;
					D.line = AllTok[t].stitch;
					D.val = "Error: Wrong Type!!!";
					ErrArr.push_back(D);
				}
				++t;
			}
		}
		else {
			while (t <= b) {
				if (AllTok[t].token == Token_Type::INTEGER_NUM || AllTok[t].token == Token_Type::PLUS ||
					AllTok[t].token == Token_Type::MINUS || AllTok[t].token == Token_Type::LBRACKET || AllTok[t].token == Token_Type::RBRACKET) {
					
				}
				else if (AllTok[t].token == Token_Type::ID) {
					short flag = 0;
					for (int i = 0; i < RealArr.size(); ++i) {
						if (RealArr[i].val == AllTok[t].line) {
							flag = 1;
							break;
						}
					}
					for (int i = 0; i < IntArr.size(); ++i) {
						if (IntArr[i].val == AllTok[t].line) {
							flag = 2;
							break;
						}
					}
					if (flag == 1) {
						Data D;
						D.line = AllTok[t].stitch;
						D.val = "Error: Wrong Type!!!";
						ErrArr.push_back(D);
					}
					if (flag == 0) {
						Data D;
						D.line = AllTok[t].stitch;
						D.val = "Error: ID is not determinated!!!";
						ErrArr.push_back(D);
					}
				}
				else if (AllTok[t].token == Token_Type::RTOI) {
					for (int i = t + 1; i <= b; ++i) {
						skob += (AllTok[i].line == "(");
						skob -= (AllTok[i].line == ")");
						if (skob == 0) {
							
							CheckType(t + 2, i - 1, 1);
							t = i;
							break;
						}
					}
					
				}
				else {
					Data D;
					D.line = AllTok[t].stitch;
					D.val = "Error: Wrong Type!!!";
					ErrArr.push_back(D);
				}
				++t;
			}
		}
		Pos = b;
	}
	void Analysis() {
		for (int i = 0; i < AllTok.size(); ++i) {
			if (AllTok[i].line == "=")As.push_back(i);
		}
		if (ErrFl) {
			ProgID = AllTok[1].line;
			for (int i = 2; i < AllTok.size(); ++i) {
				Pos = i;
				if (AllTok[i].line == "=") {
					break;
				}
				if (AllTok[i].line == "INTEGER") {
					f = 0;
				}
				else if (AllTok[i].line == "REAL") {
					f = 1;
				}
				if (AllTok[i].token == Token_Type::ID && AllTok[i-1].token!= Token_Type::ID){
					for (int j = 0; j < RealArr.size(); ++j) {
						if (RealArr[j].val == AllTok[i].line) {
							Data D;
							D.line = AllTok[i].stitch;
							D.val = "Error: Redefinition! ";
							ErrArr.push_back(D);
							break;
						}
					}
					for (int j = 0; j < IntArr.size(); ++j) {
						if (IntArr[j].val == AllTok[i].line) {
							Data D;
							D.line = AllTok[i].stitch;
							D.val = "Error: Redefinition! ";
							ErrArr.push_back(D);
							break;
						}
					}
					if (f) {
						Data D;
						D.line = AllTok[i].stitch;
						D.val = AllTok[i].line;
						RealArr.push_back(D);
					}
					else {
						Data D;
						D.line = AllTok[i].stitch;
						D.val = AllTok[i].line;
						IntArr.push_back(D);
					}
					
				}
			}

			while (Pos < S - 2) {
				--Pos;
				int a, b=S-2;
				short c=2;
				a = Pos+2;
				for (int i = 0; i < IntArr.size(); ++i) {
					if (IntArr[i].val == AllTok[Pos].line) {
						c = 0;
						break;
					}
				}
				if (c == 2) {
					c = 1;
				}
				for (int i = Pos + 2; i < S; ++i) {
					if (AllTok[i].line == "=") {
						b = i;
						Pos = i;
						break;
					}
					if (AllTok[i].line == "END") {
						b = i+1;
						Pos = i;
						break;
					}
				}
				b -= 2;
				
				CheckType(a, b, c);
				Pos = b + 2;
			}

		}
		if (AllTok[S - 1].line != AllTok[1].line) {
			Data D;
			D.line = AllTok[S-1].stitch;
			D.val = "Error: END ID!!!!!";
			ErrArr.push_back(D);
		}
		for (int i = 0; i < ErrArr.size();++i) {
			out << ErrArr[i].val<<" line "<< ErrArr[i].line<< "\n";
		}
		Postfix();
	}
	void PostfixBr(int l, int r,int c) {
		bool pf = 0, pfv = 0;
		int skc = 0, a, b;
		string prev;
		string Oper = "";
		for (int i = l; i <= r; ++i) {
			if (pfv == 0 && (AllTok[i].token == Token_Type::ID || AllTok[i].token == Token_Type::INTEGER_NUM || AllTok[i].token == Token_Type::REAL_NUM)) {
				Post.push_back(AllTok[i].line);
				pfv = 1;
			}
			else if (pfv == 1 && (AllTok[i].token == Token_Type::PLUS || AllTok[i].token == Token_Type::MINUS)) {
				Oper = AllTok[i].line;
			}
			else if (pfv == 1 && (AllTok[i].token == Token_Type::ID || AllTok[i].token == Token_Type::INTEGER_NUM || AllTok[i].token == Token_Type::REAL_NUM)) {
				Post.push_back(AllTok[i].line);
				Post.push_back(Oper);
				pfv = 0;
			}
			if (AllTok[i].token == Token_Type::LBRACKET) {
				skc++;
				for (int j = i + 1; j < AllTok.size(); ++j) {
					if (AllTok[j].line == "(")skc++;
					if (AllTok[j].line == ")")skc--;
					if (skc == 0) {
						b = j;
						break;
					}
				}
				PostfixBr(i + 1, b - 1,c);

				Post.push_back(AllTok[i - 1].line);
				i = b;

			}
			if (AllTok[i].line == "RTOI" || AllTok[i].line == "ITOR") {
				Post.push_back(AllTok[i].line);
				Post.push_back("CALL");
			}
		}
	}
	void Postfix() {
		bool pf = 0,pfv=0;
		int skc = 0,a,b;
		int l=3,r;
		string prev;
		string Oper = "";
		for (int i = 2; i < AllTok.size(); ++i) {
			if(i>2 && (AllTok[i].line == "INTEGER" || AllTok[i].line == "REAL")) {
				r = i - 1;
				Post.push_back(to_string(r - l));
				Post.push_back("DECL");
				l = i + 1;
			}
			
			if (AllTok[i].token == Token_Type::ID && AllTok[i - 1].token == Token_Type::ID) {
				r = i - 1;
				Post.push_back(to_string(r - l));
				Post.push_back("DECL");
				r = i;
				break;
			}
			else if(AllTok[i].line!=","){
				Post.push_back(AllTok[i].line);
			}
		}
		As.push_back(AllTok.size()-1);
		for (int h = 0; h < As.size()-1; ++h) {
			pfv = 0;
			skc = 0;
			Post.push_back(AllTok[As[h] - 1].line);
			for (int i = As[h]+1; i < As[h+1]-2; ++i) {
				if (pfv == 0 && (AllTok[i].token == Token_Type::ID || AllTok[i].token == Token_Type::INTEGER_NUM || AllTok[i].token == Token_Type::REAL_NUM)) {
					Post.push_back(AllTok[i].line);
					pfv = 1;
				}
				else if (pfv == 1 && (AllTok[i].token == Token_Type::PLUS || AllTok[i].token == Token_Type::MINUS)) {
					Oper = AllTok[i].line;
				}
				else if (pfv == 1 && (AllTok[i].token == Token_Type::ID || AllTok[i].token == Token_Type::INTEGER_NUM || AllTok[i].token == Token_Type::REAL_NUM)) {
					Post.push_back(AllTok[i].line);
					Post.push_back(Oper);
					pfv = 0;
				}
				if (AllTok[i].token == Token_Type::LBRACKET) {
					skc++;
					for (int j = i + 1; j < AllTok.size(); ++j) {
						if (AllTok[j].line == "(")skc++;
						if (AllTok[j].line == ")")skc--;
						if (skc == 0) {
							b = j;
							break;
						}
					}
					PostfixBr(i + 1, b - 1,h);
					Post.push_back(AllTok[i - 1].line);
					i = b;
				}
				if (AllTok[i].line == "RTOI" || AllTok[i].line == "ITOR") {
					Post.push_back(AllTok[i].line);
					Post.push_back("CALL");
				}
			}
			Post.push_back(" = ");
		}
		for (int i = 0; i < Post.size(); ++i) {
			out << Post[i] << " ";
		}
	}
	~Semantic() = default;
};
int main() {
	Semantic sem;
	sem.Analysis();
}
