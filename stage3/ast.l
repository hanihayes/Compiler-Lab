%{
	#define YYSTYPE struct tnode*
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	#include "y.tab.h"
	
	
	int number;
	
	

%}

%%

[0-9]+	{number = atoi(yytext);yylval = createTree(number,INTTYPE,NULL,NUM,NULL,NULL); return NUM;}
"begin" {return BEG;}
"end" 	{return END;}
"read"	{return READ;}
"write"	{return	WRITE;}
"if"	{return IF;}
"then"	{return THEN;}
"else"	{return ELSE;}
"endif"	{return ENDIF;}
"<"	    {return LT;} // boolean constucts
"<="	{return LE;}
">"	    {return GT;}
">="	{return GE;}
"=="	{return EQ;}
"!=" 	{return NE;}
"while"	{return WHILE;}
"do"	{return DO;}
"endwhile" {return ENDWHILE;}
"break" {return BREAK;}
"continue" {return CONTINUE;}
[a-z]   {yylval=createTree(0,INTTYPE,*yytext,ID,NULL,NULL); return ID; }
";"	{return *yytext;}
"="	{return *yytext;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
[ \t]     {}
[()]	{return *yytext;}
[\n]	{}
.	{yyerror("unknown character\n");exit(1);}

%%

int yywrap(void) {
	return 1;
}
