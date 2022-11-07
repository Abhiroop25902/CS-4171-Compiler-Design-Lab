#ifndef BINARYTREE_H
#define BINARYTREE_H


typedef struct node{
    struct node *left;
    void *data;
    struct node *right;
}node;

typedef struct genericBinaryTree{
    int dsize;
    node *root;
    void (*printNode)(void *);
}gBinaryTree;

gBinaryTree *createGBinaryTree(int , void (*)(void *));
void printPostOrder(gBinaryTree *);
node *creatGBTNode(gBinaryTree *,void *, node *, node *);
void printGBTree(gBinaryTree *);
void deleteGBTree(gBinaryTree **);
#endif