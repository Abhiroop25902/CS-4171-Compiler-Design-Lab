#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

typedef enum { CHAR, INT, FLOAT, OP} dataType;
typedef enum {false, true} bool;

typedef struct {
    char name[20];
    dataType dtype; 
}syntaxData;

typedef struct node{
    struct node *left;
    syntaxData data;
    struct node *right;
}node;

typedef struct syntaxTree{
    node *root;
}syntaxTree;

syntaxTree *createSyntaxTree(node *root);
void printPostOrder(syntaxTree *);
node *createSTNode(syntaxData , node *, node *);
void printSTree(syntaxTree *);
void deleteSTree(syntaxTree **);
void printSTNode(node *);
char *enumToString(dataType );
#endif