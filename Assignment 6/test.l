%{
#include<stdio.h>
#include "symTable.h"
#include "syntaxTree.h"
#include "y.tab.h"

char *yytext;
extern int scope;
%}

%%
[ \t\r\f]*                       {}
([\n])                           {yylineno++;}       
;                                {return(SEMICOLON_TOK);}
,                                {return COMMA_TOK;        }
\{                               {scope++;return(LBRAC_TOK);}
\}                               {scope--;return(RBRAC_TOK);}
\(				                 {return(LPAREN_TOK);}
\)				                 {return(RPAREN_TOK);}
\[                               {return (LBRACK_TOK);}
\]                               {return (RBRACK_TOK);}
\=                               {return (EQ_TOK);}
\*                               {return (ASTERISK_TOK);}
\+                               {return PLUS_TOK;}
\-                               {return MINUS_TOK;}
\/                               {return DIVIDE_TOK;}
\>                               {return GT_TOK;}
\<                                return LT_TOK;
>=                               return GEQU_TOK;
\<=                               return LEQU_TOK;
\=\=                              return EQ_EQ_TOK;
\+                               return PLUS_TOK;
\+\+                             return INCRMNT_TOK;
\+\=                             return ASUM_TOK;
\-                               return MINUS_TOK;
\-\-                             return DCRMNT_TOK;
\-\=                             return ADIFF_TOK;
\*                               return ASTERISK_TOK;
\*=                              return APROD_TOK;
\/                               return DIVIDE_TOK;
\/=                              return AQUOT_TOK;
&                               return BITWISE_AND_TOK;
&=                              return ABIT_AND_TOK;
&&                              return AND_TOK;
\|                               return BITWISE_OR_TOK;
\|=                              return ABIT_OR_TOK;
\|\|                              return OR_TOK;
int                              {yylval.name = strdup(yytext);return(INT_TOK);}
char                             {yylval.name = strdup(yytext);return (CHAR_TOK);}
float                            {return (FLOAT_TOK);}
if                               {return (IF_TOK);}
else                             {return (ELSE_TOK);}
while                            {return WHILE_TOK;}
do                               {return DO_TOK;}
for                              {return (FOR_TOK);}
main                             {return(MAIN_TOK);}
return                          {return (RETURN_TOK);}
break                           {return BREAK_TOK;}
[a-zA-Z_][a-zA-Z0-9_]*          {yylval.name = strdup(yytext);return (ID_TOK);}
([+-]?0x[0-9a-f]+)|([+-]?0b[01]+)|([+-]?[0-9]+) {yylval.val = atoi(yytext);return INT_CONST_TOK;}
\'.\'                         {yylval.name = strdup(yytext);return (CHAR_CONST_TOK);}

%%

void print(char *yytext){
    printf("%s\n", yytext);
}
/*
int main()
{
    int val;
    while((val = yylex()) > 0)
    {
        printf("Token ===%s; Token ID ====%d\n", yytext, val);
        
    }
    
    return(0);
}
 */
