%{
#include<stdio.h>
#include "y.tab.h"
%}

%%
\;                                      {return(SEMICOLON_TOK);}
\,                                      {return COMMA_TOK;}
\{                                      {return(LCRLY_TOK);}
\}                                      {return(RCRLY_TOK);}
\(				                        {return(LPAREN_TOK);}
\)				                        {return(RPAREN_TOK);}
\<				                        {return(LT_TOK);}
\>				                        {return(GT_TOK);}
\=                                      {return EQUAL_TOK;}
\!                                      {return NOT_TOK;}
\+                                      {return ADD_TOK;}
\-                                      {return SUB_TOK;}
\*                                      {return MUL_TOK;}
\/                                      {return DIV_TOK;}
\|\|                                    {return COND_OR_TOK;}
\&\&                                    {return COND_AND_TOK;}
\=\=                                    {return COND_EQUAL_TOK;}
\+\+                                    {return INCREMENT_TOK;}
int                                     {return(INT_TOK);}
main                                    {return(MAIN_TOK);}
float                                   {return FLOAT_TOK;}
char                                    {return CHAR_TOK;}
if                                      {return IF_TOK;}
else                                    {return ELSE_TOK;}
for                                     {return FOR_TOK;}
while                                   {return WHILE_TOK;}
return                                  {return RETURN_TOK;}
\#.*                                    {}
\/\/.*                                  {}
([a-z]|[A-Z]|\_)([a-z]|[A-Z]|[0-9]|\_)* {return ID_TOK;}
(\+|\-)?[0-9]+                          {return INT_CONST;}
(\+|\-)?[0-9]+\.[0-9]+                  {return FLOAT_CONST;} 
\'.\'                                   {return CHAR_CONST;} 
\".*\"                                  {return STRING_CONST;}
%%

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
