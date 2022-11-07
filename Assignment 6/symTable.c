#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symTable.h"


symtable symbolTable[NSYMS];

symtable *symLookUp(char *s, int scope){
   for(int i = 0; i < NSYMS; i++){
      if(symbolTable[i].name && !strcmp(symbolTable[i].name, s)){
         if(symbolTable[i].scope == scope){
            return (symbolTable+i);
         }
         return NULL;
      }
   }
   return NULL;
}

int symInsert(dataType dtype, char *s, int scope, int lineno){
   for(int i = 0; i < NSYMS; i++){
      if(!symbolTable[i].name) {
         symbolTable[i].name = strdup(s);
         symbolTable[i].lineno = lineno;
         symbolTable[i].scope = scope;
         symbolTable[i].dtype = dtype;
         return i;
      }
   }
   return -1;
}

void symTablePrint(){
   printf("\n");
   printf(".================ Symbol Table ================.\n");
   printf("| SNo. |   Dtype  |  Name    | scope | lineno |\n");
   printf(".----------------------------------------------. \n");
   for(int i = 0; i < NSYMS; i++){
      if(!symbolTable[i].name) break;
      printf("|%5d |%9s |%9s |%6d |%7d |\n", i+1, enumToString(symbolTable[i].dtype) ,symbolTable[i].name, symbolTable[i].scope, symbolTable[i].lineno);
   }
   printf(".==============================================.\n");
} 

void deleteSymbolTable(){
   for(int i = 0; i < NSYMS; i++){
      if(!symbolTable[i].name) continue;
      free(symbolTable[i].name);
   }
}