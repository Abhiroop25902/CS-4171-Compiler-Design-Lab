#ifndef SYMTABLE_H
#define SYMTABLE_H
#include "syntaxTree.h"
#define NSYMS 100

typedef struct {
   dataType dtype;
   char *name;
   int lineno;
   int scope;
}symtable;

symtable *symLookUp(char *, int );
int symInsert(dataType , char *, int , int );
void symTablePrint();
void deleteSymbolTable();
#endif

