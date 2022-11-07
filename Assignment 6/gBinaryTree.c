#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gBinaryTree.h"

typedef enum {false, true} bool;

gBinaryTree *createGBinaryTree(int dsize, void (*printNode)(void *)){
    gBinaryTree *gbt = (gBinaryTree *) malloc(sizeof(gBinaryTree));
    gbt->dsize = dsize;
    gbt->printNode = printNode;
    return gbt;
}   

void postOrder(node *root, void (*printNode)(void *)){
    if(!root) return;
    postOrder(root->left, printNode);
    postOrder(root->right, printNode);
    printNode(root->data);
}

void printPostOrder(gBinaryTree *gbt){
    if(!gbt || !(gbt->root)) return;
    printf("post order printing tree:- \n");
    postOrder(gbt->root, gbt->printNode);
}

node *creatGBTNode(gBinaryTree *gbt, void *data, node *left, node *right){
    node *x = (node *)malloc(sizeof(node));
    //printf("size = %ld\n", gbt->dsize);
    x->data = malloc(gbt->dsize);
    memcpy(x->data, data, gbt->dsize);
    x->left = left;
    x->right = right;
    return x;
}

void printPrettyGBTree(gBinaryTree *gbt, char *prefix, node *x, bool isLeft){
    if(!x) return;
    printf("%s", prefix);
    printf((isLeft ? "├──" : "└──" ));
    gbt->printNode(x->data);
    char temp[50];
    strcpy(temp,prefix);
    strcpy(prefix+strlen(prefix), (isLeft ? "│   " : "    "));
    printPrettyGBTree(gbt, prefix, x->left, true);
    strcpy(prefix, temp);
    strcpy(prefix+strlen(prefix), (isLeft ? "│   " : "    "));
    printPrettyGBTree(gbt, prefix, x->right, false);
}

void printGBTree(gBinaryTree *gbt){
    char prefix[50] = "";
    printf("\n\n");
    printPrettyGBTree(gbt, prefix, gbt->root, false);
}

void deleteGBTreeNode(gBinaryTree **gbt, node **x){
    if(!x || !(*x)) return;
    deleteGBTreeNode(gbt, &((*x)->left));
    deleteGBTreeNode(gbt,  &((*x)->right));

    (*gbt)->printNode((*x)->data);
    printf("  deleted\n");
    free((*x)->data);
    free((*x));
}

void deleteGBTree(gBinaryTree **gbt){
    deleteGBTreeNode(gbt, &((*gbt)->root));
    free(*gbt);
    *gbt = NULL;
}