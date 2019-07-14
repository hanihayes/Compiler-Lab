#include "y.tab.h"
//#include "arith.h"
//extern int yyparse(void);
int var_array[26];
int g=0;

reg_index codeGen( struct tnode *t) {
  int x,y,z;
  int l,m,n;
   
 switch(t->nodetype){
 
          
	case READ:                //considering only one small letter var and assigning in top of stack..........
		x=getreg();
		int stackpos;
		stackpos=4096+(*(t->left->varname))-'a';
		fprintf(xsm_fl,"MOV R%d, \"%s\"\n",x,"Read");
		    fprintf(xsm_fl,"PUSH R%d\n",x);
		    fprintf(xsm_fl,"MOV R%d, %d\n",x,-1);
		    fprintf(xsm_fl,"PUSH R%d\n",x);
		    fprintf(xsm_fl,"MOV R%d, %d\n",x,stackpos);
                   fprintf(xsm_fl,"PUSH R%d\n",x);
                    fprintf(xsm_fl,"PUSH R0\n");
		    fprintf(xsm_fl,"PUSH R0\n");
		    fprintf(xsm_fl,"CALL 0\n");
		    fprintf(xsm_fl,"POP R%d\n",x);
		    fprintf(xsm_fl,"POP R0\n");
		    fprintf(xsm_fl,"POP R0\n");
		    fprintf(xsm_fl,"POP R0\n");
		    fprintf(xsm_fl,"POP R0\n");		
		return x;
		break;
	case WRITE:
		x=getreg();
		l=codeGen(t->left);
		fprintf(xsm_fl,"MOV R%d, \"%s\"\n",x,"Write");
		    fprintf(xsm_fl,"PUSH R%d\n",x);
		    fprintf(xsm_fl,"MOV R%d, %d\n",x,-2);
		    fprintf(xsm_fl,"PUSH R%d\n",x);
                    fprintf(xsm_fl,"PUSH R%d\n",l);
                    fprintf(xsm_fl,"PUSH R0\n");
		    fprintf(xsm_fl,"PUSH R0\n");
		    fprintf(xsm_fl,"CALL 0\n");
		    fprintf(xsm_fl,"POP R%d\n",x);
		    fprintf(xsm_fl,"POP R0\n");
		    fprintf(xsm_fl,"POP R0\n");
		    fprintf(xsm_fl,"POP R0\n");
		    fprintf(xsm_fl,"POP R0\n");
		freereg();
		return x;
		break;
	case NUM:
		x=getreg();
                fprintf(xsm_fl,"MOV R%d, %d\n",x,t->val);
		return x;
		break;	
	case CONN:
		if(t->left)
		    {
		    l= codeGen(t->left);
		    freereg();
		    
		    }	  	
		if(t->right)
		    {	
		    l= codeGen(t->right);
		    freereg();		    
		    }
		    return l;
		    break;
	case ID:
		    x=4096+*(t->varname)-'a';
		    y=getreg();
		    fprintf(xsm_fl,"MOV R%d, [%d]\n",y,x);
		    return y;
		    break;
	case ASSGN:
		    m=codeGen(t->right);
	            x=4096+*((t->left)->varname)-'a';
		    fprintf(xsm_fl,"MOV [%d],R%d\n",x,m);
		    return m;
		    break;	     	    	  		  
	case EX:
	     l=codeGen(t->left);
	     m=codeGen(t->right);
	     switch(*(t->varname)){
	     
	     	case '+':
	     	     fprintf(xsm_fl,"ADD R%d, R%d\n",l,m);
     	  	     freereg();
     		     break;
     	  	case '-':	     
	             fprintf(xsm_fl,"SUB R%d, R%d\n",l,m);
     	             freereg();
     	             break;
     	  	case '*':
     	  	     fprintf(xsm_fl,"MUL R%d, R%d\n",l,m);
     	             freereg();
     	             break;
     	  	case '/':
     	  	     fprintf(xsm_fl,"DIV R%d, R%d\n",l,m);
     	  	     freereg();
     	  	     break;
	     }
	     return l;
	     break;	  
 }

}
//evaluate function......................................
int evaluate(struct tnode* t)
{   int lval,rval;
    int varct;
    switch((t->nodetype))
    {
    	case CONN:
    	       if(t->left!=NULL)
    	         {
    	         lval= evaluate(t->left);
    	         }
    	       if(t->right!=NULL)
    	          {
    	          rval=evaluate(t->right);
    	          return rval;
    	          }  
    		break;
    	case ID:
    		varct=*(t->varname)-'a';
    		return var_array[varct];
    		break;
    	case ASSGN:
    		varct=*(t->left->varname)-'a';
    		rval=evaluate(t->right);
    		var_array[varct]=rval;
    		return rval;
    		break;			
    	case NUM:
    	       return t->val;
    	       break;	
        case EX:
             switch(*(t->varname)){
            case '+' : return evaluate(t->left) + evaluate(t->right);
                       break;
            case '-' : return evaluate(t->left) - evaluate(t->right);
                       break;
            case '*' : return evaluate(t->left) * evaluate(t->right);
                       break;
            case '/' : return evaluate(t->left) / evaluate(t->right);
                       break;
        }
       case READ:
       	     varct=*(t->left->varname)-'a';
       	     scanf("%d",&var_array[varct]);
       	     return var_array[varct];
       	     break;
       case WRITE: 	     	 	       
    	     rval=evaluate(t->left);
       	     printf("%d\n",rval);
       	     return rval;
       	     break;
    }


}
//function to check AST
void tnode_print(struct tnode *t)
{  fprintf(p_tree, "\n[");
  fprintf(p_tree, "val %d\n",t->val);
  fprintf(p_tree, "type %d\n",t->type);
  fprintf(p_tree, "nodetype %d\n",t->nodetype);
  switch(t->nodetype){
  case EX:
    fprintf(p_tree, "EXPR\n");
    break;
    case ASSGN:
    fprintf(p_tree, "ASSGN\n");
    break;
    case CONN:
    fprintf(p_tree, "CONN\n");
    break;
    case NUM:
    fprintf(p_tree, "NUM\n");
    break;
    case READ:
    fprintf(p_tree, "READ\n");
    break;
    case ID:
    fprintf(p_tree, "ID\n");
    break;
    case WRITE:
    fprintf(p_tree, "WRITE\n");
    break;
   
  }
  
  if(t->varname!=NULL)
  fprintf(p_tree, "varname %c\n",*(t->varname));
 fprintf(p_tree, "]\n");
}
// 
void inorder(struct tnode *t)
{ //printf("inside inorder");
if(t==NULL)
   return;
  inorder(t->left);
  tnode_print(t);
  inorder(t->right);

}
struct tnode* createTree(int val,int type,char* varname,int nodetype,struct tnode *l,struct tnode *r){
    //creating tnode.....
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    //assigning val,type,nodetype
    temp->val=val;
    temp->type=type;
    temp->nodetype=nodetype;
    //mallocing for varname
    if(varname!=NULL)
    {
    temp->varname=(char*)malloc(sizeof(char));
    *(temp->varname)=varname;
    }
    else
    {
    temp->varname=NULL;
    }
    //assigning left and right nodes....
    temp->left = l;
    temp->right = r;
    return temp;
}


/*int evaluate(struct tnode *t){
    if(t->varname == NULL){
      //  printf("%d\n",t->val);
        return t->val;
    }
    else{
        switch(*(t->varname)){
            case '+' : return evaluate(t->left) + evaluate(t->right);
                       break;
            case '-' : return evaluate(t->left) - evaluate(t->right);
                       break;
            case '*' : return evaluate(t->left) * evaluate(t->right);
                       break;
            case '/' : return evaluate(t->left) / evaluate(t->right);
                       break;
        }
    }
}*/

//To get and allocate register
int getreg()
{ if(g<20)
  return g++;
  else
  {
  printf("Out of Registers..\n"); 
  exit(1);
  }
}
//To free register
void freereg()
{if(g>0)
return g--;
}
