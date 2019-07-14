%{
	#define YYSTYPE struct tnode*
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
    #include "tree.h"	
	char *RemoveQuotes();
	char *c;
	

%}

%%

\"(.)*\" {yylval = createTree(0,STRTYPE,strdup(RemoveQuotes()),STRING,NULL,NULL,NULL,NULL); return STRING;}            
[0-9]+   {yylval = createTree(atoi(yytext),INTTYPE,NULL,NUM,NULL,NULL,NULL,NULL); return NUM;}
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
"decl"                  {return DECL;}
"enddecl"               {return ENDDECL;}
"int"                   {return INT;}
"str"                   {return STR;}
[a-zA-Z][a-zA-Z0-9]*  {c=strdup(yytext); yylval = createTree(0,INTTYPE,c,ID,NULL,NULL,NULL,NULL); return ID;}  
","	{return *yytext;}           
";"	{return *yytext;}
"="	{return *yytext;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
"%"	{return MOD;}
[ \t]     {}
[()]	{return *yytext;}
[\n]	{}
"["           {return *yytext;} 
"]"           {return *yytext;}
.	{yyerror("unknown character\n");exit(1);}

%%

char *RemoveQuotes()
{
    yytext[yyleng-1] = '\0';        
    return yytext+1;                
}

int yywrap(void) {
	return 1;
}
