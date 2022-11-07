%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symTable.h"
#include "syntaxTree.h"

int yylex();
extern int yylineno;
extern char *yytext;
void yyerror(char *);
void print(char *);
void checkAndInsert(char *, int , int );
dataType getType(char *, int );
int scope=0;
int x = 0;
node * left = NULL, *right = NULL;
dataType varType;
%}

%union{
        double dval;
        int val;
        char *name;
        node *sNode;
}

%type <sNode> EXPRESSION
%type <sNode> ASSIGNMENT
%type <sNode> id_token
%type <name> datatype
%type <name> INT_TOK
%type <val> INT_CONST_TOK
%type <name> CHAR_TOK
%type <name> CHAR_CONST_TOK


%token SEMICOLON_TOK
%token LBRAC_TOK
%token RBRAC_TOK
%token LPAREN_TOK
%token RPAREN_TOK
%token LBRACK_TOK
%token RBRACK_TOK
%token INT_TOK
%token CHAR_TOK
%token FLOAT_TOK
%token INT_CONST_TOK
%token CHAR_CONST_TOK
%token MAIN_TOK
%token COMMA_TOK
%token <name> ID_TOK
%token EQ_TOK
%token IF_TOK
%token ELSE_TOK
%token GT_TOK
%token EQ_EQ_TOK
%token LT_TOK
%token GEQU_TOK
%token LEQU_TOK
%token PLUS_TOK
%token INCRMNT_TOK
%token ASUM_TOK
%token MINUS_TOK
%token DCRMNT_TOK
%token ADIFF_TOK
%token ASTERISK_TOK
%token APROD_TOK
%token DIVIDE_TOK
%token AQUOT_TOK
%token BITWISE_AND_TOK
%token ABIT_AND_TOK
%token AND_TOK
%token BITWISE_OR_TOK
%token ABIT_OR_TOK
%token OR_TOK
%token FOR_TOK
%token WHILE_TOK
%token DO_TOK
%token RETURN_TOK
%token BREAK_TOK

%left PLUS_TOK, MINUS_TOK
%left ASTERISK_TOK, DIVIDE_TOK

%start S



%%

S : G MAIN
  ;
G : G DECLARATION SEMICOLON_TOK     {}
  | G FUNCTION_DECL       {}
  | G ASSIGNMENT SEMICOLON_TOK  {}
  |
  ;

MAIN    :  datatype  MAIN_TOK LPAREN_TOK RPAREN_TOK BLOCK    {}
     ;

BLOCK: LBRAC_TOK  STATEMENTS  BLOCKS  RBRAC_TOK        {}
     ;

BLOCKS: BLOCK STATEMENTS BLOCKS                                {}
      |
      ;

STATEMENTS:STATEMENTS  stmt
          |
          ;

stmt      : DECLARATION SEMICOLON_TOK   {printf("decalration done\n");}
          | FUNCTION_DECL               {}
          | ASSIGNMENT SEMICOLON_TOK    {printf("assignment done\n");}
          | EXPRESSION SEMICOLON_TOK        {}
          | CONDITIONAL {}
          | LOOP        {}
          | BREAK_TOK SEMICOLON_TOK
          | RETURN_TOK EXPRESSION SEMICOLON_TOK
          ;

LOOP        : FOR
            | WHILE 
            | DO_WHILE SEMICOLON_TOK

FOR : FOR_TOK LPAREN_TOK EXPRESSION SEMICOLON_TOK EXPRESSION SEMICOLON_TOK EXPRESSION RPAREN_TOK BLOCK 
        ;
WHILE : WHILE_TOK LPAREN_TOK EXPRESSION RPAREN_TOK BLOCK
        ;
DO_WHILE : DO_TOK BLOCK WHILE_TOK EXPRESSION {}
          ;
CONDITIONAL : CONDITIONAL ELSE_TOK CONDITIONAL          
            | CONDITIONAL ELSE_TOK BLOCK        
            |IF_TOK LPAREN_TOK EXPRESSION RPAREN_TOK BLOCK 
            |
            ;

         
ASSIGNMENT : ID_TOK EQ_TOK EXPRESSION      
           {
                //printf("id_tok = %s\n", $1);
                syntaxData sd1;
                strcpy(sd1.name, $1);
                sd1.dtype = getType($1, scope);
                node *x1 = createSTNode(sd1, NULL, NULL);
                syntaxData sd = {"=", OP};
                $$ = createSTNode(sd, x1, $3);
                syntaxTree *st = createSyntaxTree($$);
                printSTree(st);
                checkType(st);
                deleteSTree(&st);
           }
           | ASSIGNMENT COMMA_TOK ID_TOK EQ_TOK EXPRESSION {}
           | ID_TOK EQ_TOK EXPRESSION COMMA_TOK ASSIGNMENT {}
           ;

EXPRESSION : ID_TOK                             
           {
                syntaxData sd1;
                strcpy(sd1.name, $1);
                sd1.dtype = getType($1, scope);
                $$ = createSTNode(sd1, NULL, NULL);
           }
           | INT_CONST_TOK                      
           {
                //printf("int_const = %d\n", $1);
                syntaxData sd;
                sprintf(sd.name, "%d", $1);
                sd.dtype = INT;
                $$ = createSTNode(sd, NULL, NULL);
           }
           | CHAR_CONST_TOK                     {
                syntaxData sd;
                strcpy(sd.name, $1);
                sd.dtype = CHAR;
                $$ = createSTNode(sd, NULL, NULL);
           }
           | EXPRESSION ASTERISK_TOK  EXPRESSION  
           {
                syntaxData sd = {"*", OP};
                $$ = createSTNode(sd, $1, $3);
           }               
           | EXPRESSION DIVIDE_TOK EXPRESSION                   {}
           | EXPRESSION PLUS_TOK EXPRESSION                   
           {
                syntaxData sd = {"+", OP};
                $$ = createSTNode(sd, $1, $3);
           }
           | EXPRESSION MINUS_TOK EXPRESSION                   {}
           | EXPRESSION GT_TOK EXPRESSION                   {}
           | EXPRESSION GEQU_TOK EXPRESSION                   {}
           | EXPRESSION LT_TOK EXPRESSION                   {}
           | EXPRESSION LEQU_TOK EXPRESSION                   {}
           | EXPRESSION EQ_EQ_TOK EXPRESSION                   {}
           | ASSIGNMENT                                 {}
           | DECLARATION                                {}
           | LPAREN_TOK EXPRESSION RPAREN_TOK   {}
           | ID_TOK LPAREN_TOK params RPAREN_TOK {}
           ;
DECLARATION:datatype id_token      
        {
            //printf("var = %s, type = %s\n", $2, $1 );
            //checkAndInsert($2, scope, yylineno);
        }
        ;

FUNCTION_DECL : datatype ID_TOK LPAREN_TOK decl_param RPAREN_TOK BLOCK
               ;

datatype:  INT_TOK { varType = INT;}
        | CHAR_TOK { varType = CHAR;}
        ;

decl_param : datatype ID_TOK {}
            | decl_param COMMA_TOK decl_param {}
            ;
params : ID_TOK
        | INT_CONST_TOK
        | params COMMA_TOK ID_TOK
        | params COMMA_TOK INT_CONST_TOK
        ;
        
id_token: ID_TOK  {
                printf("var = %s\n", $1);
                checkAndInsert($1, scope, yylineno);
        }| ID_TOK LBRACK_TOK INT_CONST_TOK RBRACK_TOK {
                printf("array decalred successfully\n");
                checkAndInsert($1, scope, yylineno);
        }| ID_TOK EQ_TOK EXPRESSION {
                printf("var = %s\n", $1);
                checkAndInsert($1, scope, yylineno);
                syntaxData sd1;
                strcpy(sd1.name, $1);
                sd1.dtype = getType($1, scope);
                node *x1 = createSTNode(sd1, NULL, NULL);
                syntaxData sd = {"=", OP};
                $$ = createSTNode(sd, x1, $3);
                syntaxTree *st = createSyntaxTree($$);
                printSTree(st);
                checkType(st);
                deleteSTree(&st);
        }| id_token COMMA_TOK id_token{}
        ;


%%




int main()
{
   printf("\nParsing begins ....\n");
   yylineno = 1;
   if (yyparse()==0) printf("Parsed Successfully\n");
   else printf("\nParsing Error at Line No %d \n", yylineno);
   
   //symTablePrint();
   deleteSymbolTable();
   return(0);	

}

void yyerror(char *s)
{
	printf("yyerror: at lineno:%d %s\n",yylineno, s);
        exit(0);
}

void checkAndInsert(char *s, int scope, int yylineno){
        if(!symLookUp(s, scope)){
                if(symInsert(varType, s, scope, yylineno) == -1){
                        yyerror("Symbol Table overflow\n");
        }
        }else{
                printf("\nSymbol \"%s\" redeclared : lineno = %d\n", s, yylineno);
                exit(0);
        }
}

dataType getType(char *s, int scope){
        symtable *st = symLookUp(s, scope);
        if(st == NULL) return -1;
        return st->dtype;
}

void checkSubexpType(node *root, dataType dtype){
        if(!root) return;
        if(!(root->right) && !(root->left)){
                //printf("%d %d\n", root->data.dtype, dtype);
                if(root->data.dtype != dtype){
                        yyerror(" subexpression type mismatch");
                }
                return;
        }
        checkSubexpType(root->left, dtype);
        checkSubexpType(root->right, dtype);
}

dataType getLeftMostType(node *root){
        if(!root) return -1;
        if(!(root->right) && !(root->left)){
                return root->data.dtype;
        }
        return getLeftMostType(root->left);
}
void checkType(syntaxTree *st){
        dataType expType = getLeftMostType(st->root->right);
        if(expType != st->root->left->data.dtype){
                yyerror(" assignment type mismatch");
        }
        checkSubexpType(st->root->right, expType);
}