%{
#include<stdio.h>

#include "LEX.h"
%}

%%
;                                           {return SEMICOLON_TOK;}
,                                           {return COMMA_TOK;}
\{                                          {return LCRLY_TOK;}
\}                                          {return RCRLY_TOK;}
\(				                            {return LPAREN_TOK;}
\)				                            {return RPAREN_TOK;}
\=                                          {return EQUAL_TOK;}
\/                                          {return DIVIDE_TOK;}
\*                                          {return STAR_TOK;}
\%                                          {return MOD_TOK;}
\+                                          {return PLUS_TOK;}
\-                                          {return MINUS_TOK;}
\!                                          {return NOT_TOK;}
\&                                          {return AND_TOK;}
\|                                          {return OR_TOK;}
\^                                          {return XOR_TOK;}
\~                                          {return COMPLEMENT_TOK;}
\[                                          {return SQUARE_BRACKET_START_TOK;}
\]                                          {return SQUARE_BRACKET_END_TOK;}
\-\=                                        {return MINUS_EQUAL_TOK;}
\<\=                                        {return LESS_EQUAL_TOK;}
\>\=                                        {return GREATER_EQUAL_TOK;}
\+\+                                        {return PLUS_PLUS_TOK;}
\-\-                                        {return MINUS_MINUS_TOK;}
\/\=                                        {return SLASH_EQUAL_TOK;}
\*\=                                        {return STAR_EQUAL_TOK;}
\!\=                                        {return NOT_EQUAL_TOK;}
\%\=                                        {return MOD_EQUAL_TOK;}
\+\=                                        {return PLUS_EQUAL_TOK;}
\^\=                                        {return XOR_EQUAL_TOK;}
\=\=                                        {return EQUAL_EQUAL_TOK;}
\&\&                                        {return AND_AND_TOK;}
\|\|                                        {return OR_OR_TOK;}
\>\>                                        {return RIGHT_SHIFT_TOK;}
\<\<                                        {return LEFT_SHIFT_TOK;}
int                                         {return INT_TOK;}
main                                        {return MAIN_TOK;}
for                                         {return FOR_TOK;}
while                                       {return WHILE_TOK;}
char                                        {return CHAR_TOK;}
float                                       {return FLOAT_TOK;}
if                                          {return IF_TOK;}
else                                        {return ELSE_TOK;}
long                                        {return LONG_TOK;}
return                                      {return RETURN_TOK;}
([a-z]|[A-Z]|\_)([a-z]|[A-Z]|[0-9]|\_)*     {return ID_TOK;}
[0-9]+                                      {return INT_CONST;}
(\+|\-)?[0-9]+\.[0-9]+                      {return FLOAT_CONST;} 
(\+|\-)?[0-9]+(\.[0-9]+)?\e(\+|\-)?[0-9]+   {return EXP_CONST;} 
\".*\"                                      {return STRING_CONST;}
\n                                          {}
\t                                          {}
#.*                                         {}
\/\/.*                                      {}
%%

int yywrap()
{
    return(1);
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Error: add only a filename\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
        perror("fopen() error");

    int val;
    while((val = yylex()) > 0)
        printf("\rToken === %s\tToken ID === %d\n", yytext, val); 
           
    
    return 0;
}

