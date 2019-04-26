#include <bits/stdc++.h>
#include "parser_tradutor.h"
# include "VM.h"

using namespace std;

int main(){
  
  // Code name
  ifstream stream1("cod.cmpuc");
  
  Parser_tradutor tradutor;
  VM virtual_machine;
  string str, x;
  
  while(stream1>>x){
    str += x;
  }
  stream1.close();
  
  try{
    tradutor.run(str);
    
    // asm code name
    ifstream stream2("prog.asm");
    
    string comand;
    while(getline(stream2, comand)){
      virtual_machine.set_instruction(comand);
    }
    
    // asm code execution
    virtual_machine.run(); 
    stream2.close();
    
  }catch(string erro){
    cout<<erro<<endl;
  }
}
