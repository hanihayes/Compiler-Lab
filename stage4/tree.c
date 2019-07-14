#include "tree.h"
#include<stdlib.h>
#include<stdio.h>
#include "y.tab.h"

struct tnode* createTree(int intVal,int type,char* stringVal,int nodeType,struct Gsymbol *gentry,struct tnode *l,struct tnode *m,struct tnode *r){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->intVal=intVal;
    temp->type=type;
    temp->nodeType=nodeType;
    temp->gentry=gentry;
    temp->stringVal=stringVal;
    temp->left = l;
    temp->mid = m;
    temp->right = r;
	typecheck(temp);
    return temp;
}

void typecheck(struct tnode* node)
{
    struct Gsymbol* p = NULL;
    int leftdata, rightdata;
    switch (node->nodeType)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case LT:
        case GT:
        case LE:
        case GE:
        case NE:
        case EQ:
            if(node->left->nodeType == ID)  leftdata = node->left->gentry->type;
            else leftdata = node->left->type;
            if(node->right->nodeType == ID)  rightdata = node->right->gentry->type;
            else rightdata = node->right->type;
            if(leftdata == rightdata)   return;
            printf("Type mismatch in expression\n"); exit(1);           
            break;

        case IF:
            if(node->left->type == BOOLTYPE) return;
            printf("Error: Type mismatch in if/while node\n"); exit(1);
            break;

        case READ:                                                              // I doubt this would ever happen; Atleast for now the grammar rules are enough
            if(node->left->nodeType == ID) return;
            printf("type mismatch in Read node\n"); exit(1);
            break;

        case WRITE:
            if(node->left->nodeType == ID)    if(node->left->gentry->type == INTTYPE || node->left->gentry->type == STRTYPE)    return;
            if(node->left->type == INTTYPE || node->left->type == STRTYPE) return;
            printf("Type mismatch in Write node\n"); exit(1);
            break;

        case ASSGN:
            if(node->left->nodeType == ID)
            {
                
                leftdata = node->left->gentry->type;
                if(node->right->nodeType == ID) rightdata = node->right->gentry->type;
                else rightdata = node->right->type; 
                if(leftdata == rightdata) return;
            }
            printf("Error: Type mismatch in assignment node\n"); exit(1);
            break;

        case ID:
            if(node->right != NULL)
            {

                if(node->right->nodeType == ID) rightdata = node->right->gentry->type;
                else rightdata = node->right->type;
                if(node->left->nodeType == ID) leftdata = node->left->gentry->type;
                else leftdata = node->left->type;
                if(leftdata == rightdata && rightdata == INTTYPE) return;
            }
            else if(node->left != NULL)
            
            {
                if(node->left->nodeType == ID) leftdata = node->left->gentry->type;
                else leftdata = node->left->type;
                if(leftdata == INTTYPE) return;
            }
            else {return;}
            printf("ERROR: Type mismatch in array declaration index\n");printf("%d,%d\n",leftdata,rightdata); exit(1);    
            break;

        default:
            break;
    }
}