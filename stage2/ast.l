%{
	#define YYSTYPE struct tnode*
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	#include "y.tab.h"
	
	
	int number;
	
	

%}

%%

[0-9]+	{number = atoi(yytext);yylval = createTree(number,0,NULL,NUM,NULL,NULL); return NUM;}
"begin" {return BEG;}
"end" 	{return END;}
"read"	{return READ;}
"write"	{return	WRITE;}
[a-z]   {yylval=createTree(0,0,*yytext,ID,NULL,NULL); return ID; }
";"	{return *yytext;}
"="	{return *yytext;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
[ \t]	{}
[()]	{return *yytext;}
[\n]	{}
.	{yyerror("unknown character\n");exit(1);}

%%

int yywrap(void) {
	return 1;
}
