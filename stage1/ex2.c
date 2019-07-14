int g = -1;
struct tnode* makeLeafNode(int n){
	struct tnode *temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->op = NULL;
	temp->val = n;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
	}
	
	struct tnode* makeOperatorNode(char c,struct tnode *l,struct tnode *r){
	struct tnode *temp;
	temp = (struct tnode*)malloc(sizeof(struct tnode));
	temp->op = malloc(sizeof(char));
	*(temp->op) = c;
	temp->left = l;
	temp->right = r;
	return temp;
	}
	
	int evaluate(struct tnode *t){
	if(t->op == NULL){
	return t->val;
	}
	else{
	switch(*(t->op)){
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
	}

	int getreg(){
	g++;
	return g;
	}
int freereg(){
	//if(rg>=0)
	   g--;
	return g;
	}
int codeGen(struct tnode *tnode){
	int p,i,j;
	if(tnode->op==NULL){
		p= getreg();
		fprintf(xsm_fl,"MOV R%d, %d\n",p,tnode->val);
		return p;
		}
	if(tnode->left!=NULL){
		i=codeGen(tnode->left);
		}
	if(tnode->right!=NULL){
		j=codeGen(tnode->right);
		}
	switch(*(tnode->op)){
	case '+' : fprintf(xsm_fl,"ADD R%d, R%d\n",i,j);
	break;
	case '-' : fprintf(xsm_fl,"SUB R%d, R%d\n",i,j);
	break;
	case '*' : fprintf(xsm_fl,"MUL R%d, R%d\n",i,j);
	break;
	case '/' : fprintf(xsm_fl,"DIV R%d, R%d\n",i,j);
	break;
	}
	freereg();
	return i;
	}

	void preorder(struct tnode *tnode)
	{
    		if(tnode->op!=NULL)
      			printf("%c",*tnode->op);
    		else
     			printf("%d",tnode->val);
		if(tnode->left!=NULL)     
			preorder(tnode->left);
		if(tnode->right!=NULL) 
			preorder(tnode->right);
		return;
	}
