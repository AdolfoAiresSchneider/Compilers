#include <bits/stdc++.h>
#include "lexer.h"
using namespace std;

class Parser{
  #define Erro1 string("Expressao incorreta")
  private :
  
    int id, flag;
    Lexer * lex;
    vector<Token> tokens;
    
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
    
  public :
  
    Parser() : id(0), flag(0), lex(new Lexer()){}
    
   ~Parser(){}
    
    void run(string str);
};


void Parser::run(string str){
    id = 0;
    tokens = lex->get_tokens(str);
    //~ for(auto x : tokens){
      //~ cout<<get_str_Type(x.type)<<' '<<x.value<<endl;
    //~ }
    process();
}
Token Parser::next_token(){
  if(id >= sz(tokens)) {
    string("Expressao incompleta");
  }
  return tokens[id++];
}

void Parser::process(){
  if(id == sz(tokens)) return ;
  instrucao();
  if(next_token().value == ";"){
    instrucao();
  }else throw Erro1;
}

void Parser::instrucao(){
  if(id >= sz(tokens)) return;
  Token token = next_token();
  
  if(token.type == ID){
    if(next_token().value != "=") throw Erro1;
    expressao();
  }else if(token.type == ESCREVA){
    if(next_token().value == "("){
      expressao();
      if(next_token().value != ")") 
        throw Erro1;
    }else throw Erro1;
    
  }else if(token.type == LEIA){
    if(next_token().value == "("){
      if(next_token().type != ID) throw Erro1;
      if(next_token().value != ")") throw Erro1;
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
    this->termo();
  }else id--;
}

void Parser::fator(){
  if(next_token().value == "("){
    this->expressao();
    if(next_token().value != ")") throw Erro1;
    return;
  } id--;
  this->base();
  this->resto3();
}

void Parser::resto3(){
  if(next_token().value == "^"){
    this->expoente();
  }else id--;
}

void Parser::base(){
  token_Type type = next_token().type;
  if(type != ID && type != NUM) throw Erro1;
}

void Parser::expoente(){
  this->base();
}
