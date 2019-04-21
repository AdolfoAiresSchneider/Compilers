#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

int main(){
  
  freopen("in", "r", stdin);// leitura de arquivo
  //~ freopen("out.txt", "w", stdout);
  
  string x, str;
  Parser parser;
  while(cin>>x){
    str += x;
  }
  try{
     parser.run(str);
     cout<<"Hásserrtou mizeravi !!"<<endl;
  }catch(string erro){
    cout<<erro<<endl;
  }
}
