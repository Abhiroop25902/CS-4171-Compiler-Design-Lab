#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntaxTree.h"



char *enumToString(dataType dtype){
    switch (dtype)
    {
    case CHAR : return "CHAR";
    case INT : return "INT";
    case FLOAT : return "FLOAT";
    case OP : return "OP";
    default:
        break;
    }
}

void printSTNode(node *x){
    printf("{name : %s , dtype : %s}\n", x->data.name, enumToString(x->data.dtype));
}
syntaxTree *createSyntaxTree(node *root){
    syntaxTree *st = (syntaxTree *) malloc(sizeof(syntaxTree));
    st->root = root;
    return st;
}

node *createSTNode(syntaxData sd, node *left, node *right){
    node *x = (node *) malloc(sizeof(node));
    strcpy(x->data.name, sd.name);
    x->data.dtype = sd.dtype;
    x->left = left;
    x->right = right;
    return x;
}


void postOrder(node *root){
    if(!root) return;
    postOrder(root->left);
    postOrder(root->right);
    printSTNode(root);
}

void printPostOrder(syntaxTree *st){
    if(!st || !(st->root)) return;
    printf("post order printing tree:- \n");
    postOrder(st->root);
}


void printPrettySTree(syntaxTree *st, char *prefix, node *x, bool isLeft){
    if(!x) return;
    printf("%s", prefix);
    printf((isLeft ? "├──" : "└──" ));
    printSTNode(x);
    char temp[50];
    strcpy(temp,prefix);
    strcpy(prefix+strlen(prefix), (isLeft ? "│   " : "    "));
    printPrettySTree(st, prefix, x->left, true);
    strcpy(prefix, temp);
    strcpy(prefix+strlen(prefix), (isLeft ? "│   " : "    "));
    printPrettySTree(st, prefix, x->right, false);
}

void printSTree(syntaxTree *st){
    char prefix[50] = "";
    printf("\n\n");
    printPrettySTree(st, prefix, st->root, false);
}

void deleteSTreeNode(node **x){
    if(!x || !(*x)) return;
    deleteSTreeNode(&((*x)->left));
    deleteSTreeNode(&((*x)->right));
    // printSTNode((*x));
    //printf("deleted\n");
    free((*x));
}

void deleteSTree(syntaxTree **st){
    deleteSTreeNode(&((*st)->root));
    (*st)->root = NULL;
    free(*st);
    *st = NULL;
}