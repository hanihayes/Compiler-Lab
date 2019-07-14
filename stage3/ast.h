//defining constants
#define reg_index int;
FILE *yyin;
struct tnode* createTree(int val,int dataType,char* varname,int nodeType,struct tnode *l,struct tnode *r);
void typecheck(struct tnode* node);	
void inorder(struct tnode *t);
void tnode_print(struct tnode *t);
int getreg();
void freereg();	
FILE *xsm_fl;
FILE *p_tree;
typedef struct tnode { 
	int val;	// value of a number for NUM nodes.
	int dataType;	//type of variable
	char* varname;	//name of a variable for ID nodes  
	int nodeType;  // information about non-leaf nodes - read/write/connector/+/* etc.  
	struct tnode *left,*right;	//left and right branches   
}tnode;
struct label_node
{
  int break_label_val;
  int continue_label_val;
  struct label_node* next;

};		
/*To evaluate an expression tree*/
int evaluate(struct tnode *t);
reg_index codeGen( struct tnode *t);
int lbpop();
void lbpush(int,int);
void backup_stack(int p,int i);
void answer_storer();

