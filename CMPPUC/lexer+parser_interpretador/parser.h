#include <bits/stdc++.h>
#include "lexer.h"
using namespace std;

class Parser{
  #define Erro1 string("Expressao incorreta!")
  #define Erro2 string("Divisão por zero!")
  #define Debug string("It is a TRAAAP")
  
  private :
  
    int id, flag;
    Lexer * lex;
    vector<Token> tokens;
    unordered_map<string, int> mem;
    stack<double> stc;
    
    Token next_token();
    void expressao();
    void instrucao();
    void expoente();
    void process();
    void resto1();
    void resto2();
    void resto3();
    void termo();
    void fator();
    void base();
    void calc(string op);
    
  public :
  
    Parser() : id(0), flag(0), lex(new Lexer()){}
    
   ~Parser(){}
    
    void run(string str);
};

void Parser::calc(string op){
  int y = stc.top(); stc.pop();
  int x = stc.top(); stc.pop();
  if(op == "+") stc.push(x + y);
  else if(op == "-") stc.push(x - y);
  else if(op == "%") stc.push(x % y);
  else if(op == "*") stc.push(x * y);
  else if(op == "^") stc.push(pow(x, y));
  else if(op == "/"){
    if(!y) throw Erro2;
    stc.push(x/y);
  }
}

void Parser::run(string str){
    id = 0;
    tokens = lex->get_tokens(str);
    process();
}
Token Parser::next_token(){
  if(id >= sz(tokens)) {
    throw string("Expressao incompleta");
  }
  return tokens[id++];
}

void Parser::process(){
  if(id == sz(tokens)) return ;
  instrucao();
  if(next_token().value == ";"){
    process();
  }else throw Erro1;
}

void Parser::instrucao(){
  if(id >= sz(tokens)) return;
  Token token = next_token();
  
  if(token.type == ID){
    if(next_token().value != "=") throw Erro1;
    expressao();
    
    mem[token.value] = stc.top();
    stc.pop();
    
  }else if(token.type == ESCREVA){
    if(next_token().value == "("){
      expressao();
      if(next_token().value != ")") throw Erro1;
      
      cout<<stc.top()<<endl;
      
    }else throw Erro1;
    
  }else if(token.type == LEIA){
    if(next_token().value == "("){
      Token x = next_token();
      if(x.type != ID) throw Erro1;
      if(next_token().value != ")") throw Erro1;
      cin>>mem[x.value];
    }
  }else {
    throw Erro1;
  }
}

void Parser::expressao(){
  this->termo();
  this->resto1();
} 

void Parser::resto1(){
  string op = next_token().value;
  if(op == "+" || op == "-"){
    this->termo();
    calc(op);
    this->resto1();
  }else id--; // voltar o indice  
}

void Parser::termo(){
  this->fator();
  this->resto2();
}

void Parser::resto2(){
  string op = next_token().value;
  if(op == "*" || op == "%"  || op == "/"){
    fator();
    calc(op);
    resto2();
  }else id--;
}

void Parser::fator(){
  this->base();
  this->resto3();
}

void Parser::resto3(){
  if(next_token().value == "^"){
    expressao();
    calc("^");
  }else id--;
}

void Parser::base(){
  Token x = next_token();
  token_Type type = x.type;
  if(type != ID && type != NUM && x.value != "(") throw Erro1;
  if(x.value == "("){
	  this->expressao();
	  if(next_token().value != ")") throw Erro1;
  }else if(x.type == NUM) stc.push(atoi(x.value.c_str()));
  else stc.push(mem[x.value]);
}

void Parser::expoente(){
  this->base();
}
