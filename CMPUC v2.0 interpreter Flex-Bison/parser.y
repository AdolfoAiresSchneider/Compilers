%{
  #include<bits/stdc++.h>
  using namespace std;
  
  extern int yylex();
  extern FILE* yyin;
  
  void yyerror(string x);
  
  string buffer;
  unordered_map< string, int > mem;
  
%}

%union {
  int intValue;
  char * stringValue;
}

%token APAR FPAR
%token ADD SUB MUL DIV MOD POT
%token NUM
%token ID
%token ATRIB
%token DELIM
%token IF ELSE
%token WHILE
%token LEIA ESCREVA

%type<intValue> exp factor term expoente base NUM
%type<stringValue> ID

%%//-----------------------------------------------------------

instrucoes: instrucoes instrucao DELIM {} 
| /*Quando nada é definido, assume-se epsilon*/ 
;

instrucao: ID ATRIB exp	{ mem[$1] = $3;  }
| ESCREVA exp				    { cout<<$2<<endl;}
| LEIA ID						    { cin>>mem[$2];  }
;

exp: term 		  {$$ = $1;     }
| exp ADD term 	{$$ = $1 + $3;}
| exp SUB term 	{$$ = $1 - $3;}
;

term: factor 		    {$$ = $1;     }
| term MUL factor 	{$$ = $1 * $3;}
| term DIV factor 	{if($3 == 0) yyerror("DIV 0\n"); else $$ = $1 / $3;} // Tratar o zero
| term MOD factor   {if($3 == 0) yyerror("DIV 0\n"); else $$ = $1 % $3;}
;

factor: base         {$$ = $1;}
| base POT expoente  {$$ = pow($1, $3);}
| APAR exp FPAR 	   {$$ = $2;}
;

expoente: base	  {$$ = $1;}
| APAR exp FPAR   {$$ = $2;}
;

base: ID		{$$ = mem[$1];}
| NUM       {$$ = $1;}    
;
%% //-----------------------------------------------------------

int main(){

  try{
    yyin = fopen("code.asdf", "r");
    yyparse();
    fclose(yyin);
  }catch(string ERRO){
    cout<<ERRO<<endl;
    return 0;
  }catch(...){
    cout<<"error"<<endl;
    return 0;
  }
}

void yyerror(string x){
  throw "ERRO > " + x;
}
