#include <bits/stdc++.h>
#include "token.h"

using namespace std;

class Lexer{
	private : 
    #define maxn 1000
    #define alphabet 26
    
		int dic[maxn][alphabet], at[maxn][alphabet], cnt;
    token_Type dic_end[maxn], at_end[maxn];
    
    void add_keyWords();
    int get_id(char c);
    // hash pro automato, ex : letra = 1 
    void make_automaton();
    void add(string s, token_Type type); 
    // adicionar a string s no dic
    token_Type get_dic(string & x); 
    // verificar se esta no dic, se sim retorna o tipo
    
  public :
    vector<Token> get_tokens(string x);
    Lexer();
};

Lexer::Lexer(){
  add_keyWords();	
	make_automaton();
  cnt = 0; 
}

void Lexer::add(string s, token_Type type){
  int node = 0;
  for(int c : s){
    int & r = dic[node][c];
    if(!r) r = ++cnt;
    node = r;
  }
  dic_end[node] = type;
}

token_Type Lexer::get_dic(string & x){
  int node = 0;
  for(int c : x){
    node = dic[node][c];
    if(!node) return ERRO;
  }
  return dic_end[node];
}

void Lexer::add_keyWords(){
  add("and", OP_LOG), add("or", OP_LOG);
  add("not", OP_LOG), add("if", IF);
  add("else", ELSE), add("while", WHILE);
  add("LEIA", LEIA), add("ESCREVA", ESCREVA);
}

int Lexer::get_id(char c){
  string delim(",;)({}"), rel("<>"), arit("+/%*^");
	if(isdigit(c)) return 0;
	if(isalpha(c)) return 1;
	if(arit.find(c) != string::npos) return 2;
	if(delim.find(c) != string::npos) return 3;
	if(rel.find(c) != string::npos) return 4;
	if(c == '=') return 5;
	if(c == '!') return 6;
	if(c == '.') return 7;
	if(c == '-') return 8;
	return 9;
}
void Lexer::make_automaton(){
  
	for(int i = 0 ; i <= 20; i++) at_end[i] = token_Type(ERRO);
	at_end[6] = ID, at_end[3] = NUM, at_end[4] = NUM, at_end[2] = OP_AR;
	at_end[5] = OP_AR, at_end[7] = DELIM, at_end[9] = OP_RL, at_end[8] = ATRIB;
	at_end[1] = ID, at_end[10] = OP_RL;
  
	at[0][1] = 1, at[1][1] = 1, at[1][0] = 6, at[6][0] = 6, at[6][1] = 6;
	at[0][3] = 7, at[0][2] = 5;
	at[0][0] = 3, at[3][0] = 3, at[3][7] = 4, at[4][0] = 4;
	at[0][7] = 7, at[0][3] = 7, at[0][8] = 2, at[2][0] = 3;
	at[0][6] = 11, at[0][5] = 9, at[11][5] = 9;
	at[0][5] = 8, at[8][5] = 9, at[0][4] = 10, at[10][5] = 9;
	at[3][1] = 12, at[4][1] = 12, at[12][1] = 12, at[12][0] = 12;  
}

vector<Token> Lexer::get_tokens(string x){
	x += '$';
	
	int node = 0;
	string val;
	vector<Token> tokens;
  token_Type last = ERRO;
	
	for(char c : x){
		int id = get_id(c);
		if(!at[node][id]){
      token_Type cur_type = at_end[node];
      if(node == 1){
        token_Type y = get_dic(val);
        if(y != ERRO) cur_type = y;
      }else if(cur_type == NUM){
        if(val[0] == '-' && (last == NUM || last == ID)){
          tokens.pb({OP_AR, "-"});
          val = val.substr(1);
        }
      }
      tokens.pb({cur_type, val}), last = cur_type;
			val.clear(), node = 0;
		}
		node = at[node][id];
		val += c;
	}
	return tokens;
}
