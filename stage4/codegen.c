#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"
#include "y.tab.h"

reg_index codeGen( struct tnode *t) {
  int x,y,z;
  int l,m,n;
  int lb1=0;
  int lb2=0;
	struct Gsymbol* temp = NULL;
 switch(t->nodeType){
 
	case READ:                //considering only one small letter var and assigning in top of stack..........
		x=getreg();
		int stackpos;
		temp = lookup(t->left->stringVal);
		stackpos=temp->binding;
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
                fprintf(xsm_fl,"MOV R%d, %d\n",x,t->intVal);
		return x;
		break;	
	case STRING:
		x=getreg();
                fprintf(xsm_fl,"MOV R%d, %s\n",x,t->stringVal);
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
    	if(t->left!=NULL)
    	{
	    	l=codeGen(t->left);
    		fprintf(xsm_fl,"\nADD R%d,%d",l,t->gentry->binding);
    		fprintf(xsm_fl,"\nMOV R%d,[R%d]",l,l);
			return l;
    	}
	    else
    	{
			y=getreg();
			fprintf(xsm_fl,"MOV R%d, [%d]\n",y,t->gentry->binding);
			return y;		
	    }
	    break;
	case ASSGN:
		m=codeGen(t->right);
		temp = lookup(t->left->stringVal);
		x=temp->binding;
		    fprintf(xsm_fl,"MOV [%d],R%d\n",x,m);
		    return m;
		    break;
	case PLUS:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"ADD R%d, R%d\n",l,m);
		freereg();
		return l;
		break;
	case MINUS:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"SUB R%d, R%d\n",l,m);
		freereg();
		return l;
		break;
	case MUL:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"MUL R%d, R%d\n",l,m);
		freereg();
		return l;
		break;
	case DIV:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"DIV R%d, R%d\n",l,m);
		freereg();
		return l;
		break;
	case MOD:
		l=codeGen(t->left);
		m=codeGen(t->right);
		fprintf(xsm_fl,"MOD R%d, R%d\n",l,m);
		freereg();
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
	        m=codeGen(t->mid); 
	        if(t->right!=NULL)
	        {
	         lb2=getLabel();
	         fprintf(xsm_fl,"JMP L%d\n",lb2);
	        }    	  
 	         fprintf(xsm_fl,"L%d:\n",lb1);
 	        if(t->right!=NULL)
 	        {
 	        freereg();
 	        m=codeGen(t->right);
 	        fprintf(xsm_fl,"L%d:\n",lb2);
 	        } 
 	        return m;
 	        break;
	case WHILE:
		 lb1=getLabel();	        
		 lb2=getLabel();
		 lbpush(&head,lb2,lb1);
		 fprintf(xsm_fl,"L%d:\n",lb1);
    	         l=codeGen(t->left);
    	         fprintf(xsm_fl,"JZ R%d, L%d\n",l,lb2);
    	         m=codeGen(t->right);
    	         freereg();
    	         fprintf(xsm_fl,"JMP L%d\n",lb1);
    	         fprintf(xsm_fl,"L%d:\n",lb2);
		 lbpop(&head);
		 return l;
		 break;

    case BREAK:
  		x=getreg();
  		z=lbpop(&head);
    	fprintf(xsm_fl,"JMP L%d\n",z);
  		return x;
      		
    case CONTINUE: 
        x=getreg();
  		z=head->continue_label_val;
  		fprintf(xsm_fl,"JMP L%d\n",z);
  		return x;
 }

}

void lbpush(struct label_node **head,int break_val,int cont_val)
{
  struct label_node *temp;
  temp=(struct label_node*)malloc(sizeof(struct label_node));
  temp->break_label_val=break_val;
  temp->continue_label_val=cont_val;
  temp->next=*head;
  *head=temp;
}

int lbpop(struct label_node **head)
{
	if(*head==NULL)
	{
	  return -1; 
	}
	else
	{  int temp=(*head)->break_label_val;
	   *head=(*head)->next;
		return temp;
	}
}

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