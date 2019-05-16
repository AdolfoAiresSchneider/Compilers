all: COMPILER lex.yy.c parser.tab.h parser.tab.c clean

COMPILER: lex.yy.c parser.tab.c parser.tab.h
	 g++ -o COMPILER lex.yy.c parser.tab.c -lfl

lex.yy.c: lexer.l parser.tab.h	
	flex lexer.l

parser.tab.h parser.tab.c: parser.y
	bison -d parser.y

clean:
	 @rm lex.yy.c parser.tab.c parser.tab.h
