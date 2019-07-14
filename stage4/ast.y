%{
	#define YYSTYPE struct tnode*
	#include <stdio.h>
	#include <stdlib.h>
	#include "tree.c"
	#include "tree.h"
	#include "codegen.c"
	#include "codegen.h"
	#include "symbol.c"
	#include "symbol.h"
	int yylex(void);
	int yyerror(char const *);
	int t=0;


%}
%token NUM BEG READ WRITE END ASGN ID IF THEN WHILE ENDWHILE ENDIF DO ELSE BREAK CONTINUE 
%token DECL ENDDECL INT STR CONN INTTYPE STRTYPE BOOLTYPE VARIABLE STRING
%right ASSGN
%left PLUS MINUS
%left MUL DIV MOD
%nonassoc LT GT LE GE EQ NE

%%

program: DeclBlock BEG Slist END';' { $$ = $3; codeGen($3); dispg();}
    	| DeclBlock BEG END';'           {exit(0);} 
		;

DeclBlock: DECL DeclList ENDDECL  
         | DECL ENDDECL           
		;

DeclList: Declaration
        | DeclList Declaration
		;

Declaration: Type VarList ';'          {varinstall($1->type,$2);}
;

Type: INT                                   {$$ = createTree(0,INTTYPE,NULL,0,NULL,NULL,NULL,NULL);}
    | STR                                   {$$ = createTree(0,STRTYPE,NULL,0,NULL,NULL,NULL,NULL);}
;

VarList: Variable
            | VarList ',' Variable     {$$ = createTree(0,0,NULL,CONN,NULL,$1,NULL,$3);}
;

Variable: ID                      {$1->intVal = 1; $$ = $1;} 
         | ID'['NUM']'            {$1->intVal = $3->intVal; $$ = $1;}
;            	

Slist: Slist Stmt       {$$=createTree(0,0,NULL,CONN,NULL,$1,NULL,$2);}   
     | Stmt             {$$=$1;}
 ;

Stmt: expr '=' expr ';'     {$$ = createTree(0,0,'=',ASSGN,NULL,$1,NULL,$3);}
    | READ '('expr')'';'   	{$$ = createTree(0,0,NULL,READ,NULL,$3,NULL,NULL);}
	| WRITE '('expr')'';' 	{$$ = createTree(0,0,NULL,WRITE,NULL,$3,NULL,NULL);}
	| IF '('expr')' THEN Slist ELSE Slist ENDIF';' {$$ = createTree(0,0,NULL,IF,NULL,$3,$6,$8);}
	| IF '('expr')' THEN Slist ENDIF';'            {$$ = createTree(0,0,NULL,IF,NULL,$3,$6,NULL);}
	| WHILE '('expr')' DO Slist ENDWHILE';' {$$=createTree(0,0,NULL,WHILE,NULL,$3,NULL,$6);}
	| BREAK';'  {$$=createTree(0,0,NULL,BREAK,NULL,NULL,NULL,NULL);}
    | CONTINUE';' {$$=createTree(0,0,NULL,BREAK,NULL,NULL,NULL,NULL);}
;

expr:   expr PLUS expr	{$$ = createTree(0,INTTYPE,'+',PLUS,NULL,$1,NULL,$3);}
	 | expr MINUS expr  {$$ = createTree(0,INTTYPE,'-',MINUS,NULL,$1,NULL,$3);}
	 | expr MUL expr	{$$ = createTree(0,INTTYPE,'*',MUL,NULL,$1,NULL,$3);}
	 | expr DIV expr	{$$ = createTree(0,INTTYPE,'/',DIV,NULL,$1,NULL,$3);}
	 | expr MOD expr	{$$ = createTree(0,INTTYPE,'%',MOD,NULL,$1,NULL,$3);}
	 | expr GT expr		{$$ = createTree(0,BOOLTYPE,NULL,GT,NULL,$1,NULL,$3);}		
	 | expr GE expr		{$$ = createTree(0,BOOLTYPE,NULL,GE,NULL,$1,NULL,$3);}
	 | expr LT expr		{$$ = createTree(0,BOOLTYPE,NULL,LT,NULL,$1,NULL,$3);}
	 | expr LE expr		{$$ = createTree(0,BOOLTYPE,NULL,LE,NULL,$1,NULL,$3);}
	 | expr EQ expr		{$$ = createTree(0,BOOLTYPE,NULL,EQ,NULL,$1,NULL,$3);}
	 | expr NE expr		{$$ = createTree(0,BOOLTYPE,NULL,NE,NULL,$1,NULL,$3);}
	 | '('expr')'		{$$ = $2;}
     | ID                     {$1->gentry = lookup($1->stringVal); if($1->gentry == NULL) {printf("Undeclared Variable\n"); exit(1);} $$ = $1;}
	 | ID'['expr']'            {$$ = createTree(0,0,$1->stringVal,ID,lookup($1->stringVal),$3,NULL,NULL);}
	 | STRING       {$$ = $1;}  
	 | NUM			    {$$ = $1;}
;

%%

yyerror(char const *s)
{
    printf("yyerror %s",s);
}


int main(int argc,char* argv[]) {
if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
}
 	p_tree=fopen("tree.txt","w");
 	xsm_fl=fopen("ast.xsm","w");
	fprintf(xsm_fl, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n ",0,2056,0,0,0,0,0,0); 
	fprintf(xsm_fl, "BRKP\n");
	fprintf(xsm_fl, "MOV SP, 4121\n");
	yyparse();
	return 0;
}
