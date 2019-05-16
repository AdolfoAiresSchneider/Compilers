%{
  #include<bits/stdc++.h>
  using namespace std;
  
  #include "parser.tab.h"
  extern string buffer;
  
%}

%option noyywrap

%% //-----------------------------------------------------------

";"       { return DELIM;   }
"+"       { return ADD;     }
"^"       { return POT;     }
"%"       { return MOD;     }
"-"       { return SUB;     }
"*"       { return MUL;     }
"/"       { return DIV;     }
"="       { return ATRIB;   }
[0-9]+    { yylval.intValue = atoi(yytext); return NUM; }
"IF"      { return IF;      }
"ELSE"    { return ELSE;    }
"ESCREVA" { return ESCREVA; }
"LEIA"    { return LEIA;    }
"WHILE"   { return WHILE;   }
"("       { return APAR;    }
")"       { return FPAR;    }
[_a-zA-Z][_a-zA-Z0-9]* { buffer = yytext; yylval.stringValue = (char*)buffer.data(); return ID; }
[" "|"\n"|"\t"] { }
. { printf("Mystery character %c\n", *yytext); }

%%//-----------------------------------------------------------

