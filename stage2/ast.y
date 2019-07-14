%{
	#define YYSTYPE struct tnode*
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	#include "ast.c"
    	int yylex(void);
    	int yyerror(char const *);


%}

%token NUM PLUS MINUS MUL DIV BEG READ WRITE END ID CONN ASSGN EX
%left PLUS MINUS
%left MUL DIV

%%
program: BEG Slist END';' { $$ = $2; codeGen($2);}
     | BEG END';'           {exit(0);} 
;
Slist: Slist Stmt       {$$=createTree(0,0,NULL,CONN,$1,$2);}   
     | Stmt             {$$=$1;}
 ;

Stmt: ID '=' expr ';'     {$$ = createTree(0,0,'=',ASSGN,$1,$3);}
    | READ '('ID')'';'   {$$ = createTree(0,0,NULL,READ,$3,NULL);}
	| WRITE '('expr')'';' {$$ = createTree(0,0,NULL,WRITE,$3,NULL);}
;

expr:   expr PLUS expr		{$$ = createTree(0,0,'+',EX,$1,$3);}
	 | expr MINUS expr    {$$ = createTree(0,0,'-',EX,$1,$3);}
	 | expr MUL expr	    {$$ = createTree(0,0,'*',EX,$1,$3);}
	 | expr DIV expr	    {$$ = createTree(0,0,'/',EX,$1,$3);}
	 | '('expr')'		{$$ = $2;}
	 | ID               {$$ = $1;}
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
