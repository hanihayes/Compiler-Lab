%{
   #include <stdio.h>
   #include <stdlib.h>

   //#define YYSTYPE tnode *
	
   #include "ex2.h"
   #include "ex2.c"
	
   int yylex(void);
	
%}
%union{ struct tnode *no;
	}	
%type <no> expr program  NUM END//PLUS MINUS MUL DIV
%token NUM PLUS MINUS MUL DIV END
%left PLUS MINUS
%left MUL DIV

%%
program : expr END{
                        $$ = $2;
                        printf("Answer : %d\n",evaluate($1));
                        //preorder($1); 
                        codeGen($1);
                        printf("\n");
                        exit(1);
                  }
                  ;
	
expr : PLUS expr expr {$$ = makeOperatorNode('+',$2,$3);}
| MINUS expr expr {$$ = makeOperatorNode('-',$2,$3);}
| MUL expr expr {$$ = makeOperatorNode('*',$2,$3);}
| DIV expr expr {$$ = makeOperatorNode('/',$2,$3);}
| '(' expr ')' {$$ = $2;}
| NUM {$$ = $1;}
;
	
%%
	
yyerror(char const *s)
{
printf("yyerror %s",s);
	}
	
	
int main(int argc, char *argv[]) {
if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
}
 	xsm_fl=fopen("exp_pre.xsm","w");
	fprintf(xsm_fl, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n",0,2056,0,0,0,0,0,0,"BRKP");
	yyparse();	
	return 0;
}

