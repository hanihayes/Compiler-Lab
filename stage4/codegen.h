#ifndef CODEGEN_H
#define CODEGEN_H
#include "tree.h"

int var_array[26];
int g=0;
int lct=0;

#define reg_index int;
FILE *yyin;
struct label_node
{
  int break_label_val;
  int continue_label_val;
  struct label_node* next;

};
struct label_node* head;
int getreg();
void freereg();	
FILE *xsm_fl;
FILE *p_tree;		
/*To evaluate an expression tree*/
reg_index codeGen( struct tnode *t);
int lbpop(struct label_node **head);
void lbpush(struct label_node **head,int break_val,int cont_val);
#endif