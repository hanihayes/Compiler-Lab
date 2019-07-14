#ifndef SYMBOL_H
#define SYMBOL_H

struct Gsymbol {
    char* name;
    int type;
    int size;
    int binding;
    struct Gsymbol *next;
};

struct Gsymbol* hd;
void Install(char *varName, int dataType, int size);    
//void varinstall(int type, struct tnode* varList);
struct Gsymbol* lookup(char *name);    
void dispg();             
#endif