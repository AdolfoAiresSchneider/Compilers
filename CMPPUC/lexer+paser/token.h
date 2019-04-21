#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define sz(a) (int)a.size()
#define pb push_back

enum token_Type{
  ID, NUM, OP_AR, OP_RL, OP_LOG, DELIM, IF, ELSE, WHILE, ATRIB, LEIA, ESCREVA, ERRO
};

string str_type[13] = {"ID", "NUM","OP_AR", "OP_RL", "OP_LOG", "DELIM", "IF", "ELSE", "WHILE", "ATRIB", "LEIA", "ESCREVA", "ERRO"};
inline string get_str_Type(token_Type x){ return str_type[x];}

struct Token{
  token_Type type;
  string value;
  Token(token_Type a, string b){
    type = a, value = b;
  }
};

