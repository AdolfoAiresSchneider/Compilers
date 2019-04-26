#include <bits/stdc++.h>
#include "lexer.h"
#include <sstream>

using namespace std;


class Parser_tradutor{
  #define Erro1 string("expression incorreta!")
  #define Erro2 string("Divisão por zero!")
  #define Erro3 string("expression incompleta");
  #define Debug string("It is a TRAAAP")
  
  private :
    ofstream out;
    int id, flag;
    Lexer * lexer;
    vector<Token> tokens;
    unordered_map<string, int> index;
    
    Token next_token();
    void expression();
    void instruc();
    void exp();
    void process();
    void resto1();
    void resto2();
    void resto3();
    void term();
    void factor();
    void base();
    void calc(string op);
    int get_id_mem(string & str);
    
  public :
    
    Parser_tradutor() : id(0), flag(0), lexer(new Lexer()){
    }
    
   ~Parser_tradutor(){}
    void run(string str);
};

int Parser_tradutor::get_id_mem(string & str){
  if(index.count(str)) return index[str];
  return index[str] = sz(index);
}

void Parser_tradutor::calc(string op){
  out<<"POP R1\nPOP R2"<<endl;
  if(op == "+") out<<"ADD ";
  else if(op == "-") out<<"SUB ";
  else if(op == "%") out<<"MOD ";
  else if(op == "*") out<<"MUL ";
  else if(op == "^") out<<"POT ";
  else if(op == "/") out<<"DIV ";
  out<<"R1 R2 R3"<<endl<<"PUSH R3"<<endl;
}

void Parser_tradutor::run(string str){
    out.open("prog.asm");
    id = 0;
    tokens = lexer->get_tokens(str);
    process();
    out.close();
}

Token Parser_tradutor::next_token(){
  if(id >= sz(tokens)) {
    throw Erro3;
  }
  return tokens[id++];
}

void Parser_tradutor::process(){
  if(id == sz(tokens)) return ;
  instruc();
  if(next_token().value == ";"){
    process();
  }else throw Erro1;
}

void Parser_tradutor::instruc(){
  if(id >= sz(tokens)) return;
  Token token = next_token();
  
  if(token.type == ID){
    if(next_token().value != "=") throw Erro1;
    expression();
    out<<"POP R2"<<endl<<"STORE R2 "<<get_id_mem(token.value)<<endl;;
  }else if(token.type == ESCREVA){
    if(next_token().value == "("){
      expression();
      if(next_token().value != ")") throw Erro1;
      out<<"POP R2\nWRITE R2"<<endl;
    }else throw Erro1;
    
  }else if(token.type == LEIA){
    if(next_token().value == "("){
      Token x = next_token();
      if(x.type != ID) throw Erro1;
      if(next_token().value != ")") throw Erro1;
      out<<"READ R1"<<endl<<"STORE R1 "<<get_id_mem(x.value)<<endl;
    }
  }else throw Erro1;
}

void Parser_tradutor::expression(){
  this->term();
  this->resto1();
} 

void Parser_tradutor::resto1(){
  string op = next_token().value;
  if(op == "+" || op == "-"){
    this->term();
    calc(op);
    this->resto1();
  }else id--;
}

void Parser_tradutor::term(){
  this->factor();
  this->resto2();
}

void Parser_tradutor::resto2(){
  string op = next_token().value;
  if(op == "*" || op == "%"  || op == "/"){
    factor();
    calc(op);
    resto2();
  }else id--;
}

void Parser_tradutor::factor(){
  this->base();
  this->resto3();
}

void Parser_tradutor::resto3(){
  if(next_token().value == "^"){
    expression();
    calc("^");
  }else id--;
}

void Parser_tradutor::base(){
  Token x = next_token();
  token_Type type = x.type;
  if(type != ID && type != NUM && x.value != "("){
    throw Erro1;
  }
  if(x.value == "("){
	  this->expression();
	  if(next_token().value != ")"){
      throw Erro1;
    }
  }else if(x.type == NUM){
     out<<"MOVE R1 " + x.value <<endl<<"PUSH R1"<<endl;  
  }
  else{
     out<<"LOAD R1 "<<get_id_mem(x.value)<<endl<<"PUSH R1"<<endl;
  }
}

void Parser_tradutor::exp(){
  this->base();
}
