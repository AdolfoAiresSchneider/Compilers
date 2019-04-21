#include <bits/stdc++.h>
#include "parser_interpredador.h"
using namespace std;

char x[100000];

int main(){
  
  FILE * stream = fopen("in", "r");
  
  Parser_inter inter;
  string str;
  
  while(fscanf(stream,"%s", x ) == 1){
    str += x;
  }
  
  try{
     inter.run(str);
  }catch(string erro){
    cout<<erro<<endl;
  }
}
