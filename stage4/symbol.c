#include "symbol.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Gsymbol* hd = NULL;
int c=0,mem=4096;

struct Gsymbol* lookup(char *name)
{
    struct Gsymbol *temp=hd;
    while(temp!=NULL)
    {
        if(strcmp(temp->name,name)==0)
            return temp;

        temp=temp->next;
    }
    return NULL;
}

void varinstall(int type, struct tnode* varList)
{
    if (varList->nodeType == CONN) {
        varinstall(type, varList->left);
        varinstall(type, varList->right);
    }
    else {
        Install(varList->stringVal, type, varList->intVal);
    }
}

void Install(char* name, int type, int size)
{
    struct Gsymbol* temp = malloc(sizeof(struct Gsymbol));
    temp->name = name;
    temp->type = type;
    temp->size = size;
    temp->binding = 4096;
    temp->next = NULL;  
    if (hd == NULL) {
        hd = temp;
        return;
    }
    struct Gsymbol* ptr = hd;
    while (1) {
        if (!(strcmp(ptr->name, name))) {
            printf("Multiple instances of variable '%s' declared\n", name);
            exit(1);
        }
        temp->binding += ptr->size;
        if (ptr->next == NULL)
            break;
        ptr = ptr->next;
    }
    ptr->next = temp;
}

void dispg()
{
    struct Gsymbol *temp=hd;
    while(temp!=NULL)
    {
        char c[10];
        switch(temp->type)
        {
            case INTTYPE :strcpy(c,"int");
            break;
            case STRTYPE :strcpy(c,"string");
            break;
        }
        printf("name:%s  type:%s  size:%d  binding:%d\n",temp->name,c,temp->size,temp->binding);
        temp=temp->next;
    }
}