#ifndef TREE_H
#define TREE_H

#include "symbol.h"

typedef struct tnode {
	int intVal;
	int type;
	char* stringVal;
	int nodeType;
	struct Gsymbol *gentry;
	struct tnode *left,*mid,*right;
}tnode;

struct tnode* createTree(int intVal,int type,char* stringVal,int nodeType,struct Gsymbol *gentry,struct tnode *l,struct tnode *m,struct tnode *r);
void typecheck(struct tnode* node);	

#endif