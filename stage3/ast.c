#include "y.tab.h"
//#include "arith.h"
//extern int yyparse(void);
int var_array[26];
int g=0;
int lct=0;
struct label_node* head;

reg_index codeGen( struct tnode *t) {
  int x,y,z;
  int l,m,n;
  int lb1=0;
  int lb2=0;
   
 switch(t->nodeType){
 
          
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
	case EQ:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"EQ R%d, R%d\n",l,m);
		freereg();
		return l;
		break;
	case NE:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"NE R%d, R%d\n",l,m);
		freereg();
		return l;
		break; 
	case GT:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"GT R%d, R%d\n",l,m);
		freereg();
		return l;
		break; 
	case GE:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"GE R%d, R%d\n",l,m);
		freereg();
		return l;
		break; 
	case LT:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"LT R%d, R%d\n",l,m);
		freereg();
		return l;
		break; 
	case LE:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"LE R%d, R%d\n",l,m);
		freereg();
		return l;
		break;
	case IF:
		lb1=getLabel();
		l=codeGen(t->left);
		fprintf(xsm_fl,"JZ R%d, L%d\n",l,lb1);
            	freereg();
	        m=codeGen(t->right->left); 
	        if(t->right->right!=NULL)
	        {
	         lb2=getLabel();
	         fprintf(xsm_fl,"JMP L%d\n",lb2);
	        }    	  
 	         fprintf(xsm_fl,"L%d:\n",lb1);
 	        if(t->right->right!=NULL)
 	        {
 	        freereg();
 	        m=codeGen(t->right->right);
 	        fprintf(xsm_fl,"L%d:\n",lb2);
 	        } 
 	        return m;
 	        break;
	case WHILE:
		 lb1=getLabel();	        
		 lb2=getLabel();
		 lbpush(lb2,lb1);
		 fprintf(xsm_fl,"L%d:\n",lb1);
    	         l=codeGen(t->left);
    	         fprintf(xsm_fl,"JZ R%d, L%d\n",l,lb2);
    	         m=codeGen(t->right);
    	         freereg();
    	         fprintf(xsm_fl,"JMP L%d\n",lb1);
    	         fprintf(xsm_fl,"L%d:\n",lb2);
		 lbpop();
		 return l;
		 break;
    case BREAK:
  		x=getreg();
  		z=head->break_label_val;
    	fprintf(xsm_fl,"JMP L%d\n",z);
  		return x;
      		
    case CONTINUE: 
        x=getreg();
  		int z=head->continue_label_val;
  		fprintf(xsm_fl,"JMP L%d\n",z);
  		return x;   
 }

}
//evaluate function......................................
int evaluate(struct tnode* t)
{   int lval,rval;
    int varct;
    switch((t->nodeType))
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
       case EQ:
	  	if(evaluate(t->left)==evaluate(t->right)){
			lval = 1;
			return lval;			}
		else {lval=0;
		return lval;}
		break; 
       case NE:
		if(evaluate(t->left)!=evaluate(t->right)){
			lval = 1;
			return lval;			}
		else {lval=0;
		return lval;}
		break;
       case GE:
		if(evaluate(t->left)>=evaluate(t->right)){
			lval = 1;
			return lval;			}
		else {lval=0;
		return lval;}
		break;
       case GT:
		if(evaluate(t->left)>evaluate(t->right)){
			lval = 1;
			return lval;			}
		else {lval=0;
		return lval;}
		break;
      case LE:
		if(evaluate(t->left)<=evaluate(t->right)){
			lval = 1;
			return lval;			}
		else {lval=0;
		return lval;}
		break;
      case LT:
		if(evaluate(t->left)<evaluate(t->right)){
			lval = 1;
			return lval;			}
		else {lval=0;
		return lval;}
		break; 
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
       case IF: 
	    lval= evaluate(t->left);
	    if(lval){
		lval = evaluate(t->right->left);
		return lval;
		}
	   else {rval =evaluate(t->right->right);
		return rval;	
			}
	   break;
       case WHILE:
	    while(evaluate(t->left)){
		rval = evaluate(t->right);
		}
		return rval;
	   break;
       case BREAK:exit(0);
	    break;
	case CONTINUE: return 0;
	    break;
    }


}
//function to check AST
void tnode_print(struct tnode *t)
{  fprintf(p_tree, "\n[");
  fprintf(p_tree, "val %d\n",t->val);
  fprintf(p_tree, "type %d\n",t->dataType);
  fprintf(p_tree, "nodetype %d\n",t->nodeType);
  switch(t->nodeType){
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
    case IF:
    fprintf(p_tree, "IF\n");
    break;
    case LT:
    case GT:
    case LE:
    case GE:
    case NE:
    case EQ:
    fprintf(p_tree, "LOG\n");
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

void lbpush(int break_val,int cont_val)
{
  struct label_node *temp;
  temp=(struct label_node*)malloc(sizeof(struct label_node));
  temp->break_label_val=break_val;
  temp->continue_label_val=cont_val;
  temp->next=head;
  head=temp;
}
int lbpop()
{
if(head==NULL)
{
  return -1; 
}
else
{  int temp=head->break_label_val;
   head=head->next;
   return temp;
}
}

struct tnode* createTree(int val,int dataType,char* varname,int nodeType,struct tnode *l,struct tnode *r){
    //creating tnode.....
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    //assigning val,type,nodetype
    temp->val=val;
    temp->dataType=dataType;
    temp->nodeType=nodeType;
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
	typecheck(temp);
    return temp;
}

void typecheck(struct tnode* node)
{
    switch (node->nodeType)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            if(node->left->dataType == INTTYPE && node->right->dataType==INTTYPE) return;
            printf("Error: Type mismatch in aritmetic operator node\n"); exit(1);           //would probably never happen; correction: "CAN" happen a=a+(a<b)
            break;
        
        case LT:
        case GT:
        case LE:
        case GE:
        case NE:
        case EQ:
            if(node->left->dataType == INTTYPE && node->right->dataType == INTTYPE) return;
            printf("Error: Type mismatch in logical operator node\n"); exit(1);
            break;

        case IF:
            if(node->left->dataType == BOOLTYPE) return;
            printf("Error: Type mismatch in if/while node\n"); exit(1);
            break;

        case READ:                                                              // I doubt this would ever happen; Atleast for now the grammar rules are enough
            if(node->left->nodeType == ID) return;
            printf("Error: type mismatch in Read node\n"); exit(1);
            break;

        case WRITE:
            if(node->left->dataType == INTTYPE) return;
            printf("Error: Type mismatch in Write node\n"); exit(1);
            break;

        case ASSGN:
            if(node->left->nodeType == ID)                                     // Again grammar rules ensure this doesn't happen
                if(node->left->dataType == node->right->dataType) return;
            printf("Error: Type mismatch in assignment node\n"); exit(1);
            break;

        default:
            break;
    }
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

//To get Label
int getLabel()
{
return lct++;
}
