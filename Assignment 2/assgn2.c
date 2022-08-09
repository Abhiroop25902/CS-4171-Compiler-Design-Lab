#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Single caharacter lexemes */
#define LPAREN_TOK '('
#define GT_TOK '>'
#define LT_TOK '<'
#define RPAREN_TOK ')'
#define EQ_TOK '='
#define MINUS_TOK '-'
#define SEMICOLON_TOK ';'
#define HASH_TOK '#'
#define CURLY_BRACKET_START_TOK '{'
#define CURLY_BRACKET_END_TOK '}'
#define SQUARE_BRACKET_START_TOK '['
#define SQUARE_BRACKET_END_TOK ']'
#define EQUAL_TOK '='
#define SEMICOLON_TOK ';'
#define PLUS_TOK '+'
#define MINUS_TOK '-'
#define DOUBLE_QUOTE_TOK '"'
#define COMMA_TOK ','
#define DIVIDE_TOK '/'
#define STAR_TOK '*'
#define MOD_TOK '%'
#define NOT_TOK '!'
#define AND_TOK '&'
#define OR_TOK '|'
#define XOR_TOK '^'
#define COMPLEMENT_TOK '~'
/*....................
.......................*/
/* Reserved words */
#define WHILE_TOK 256
#define INCLUDE_TOK 257
#define VOID_TOK 258
#define FOR_TOK 259
#define INT_TOK 260
#define FLOAT_TOK 261
#define LONG_TOK 262
#define CHAR_TOK 263
#define ELSE_TOK 264
#define PLUS_EQUAL_TOK 265
#define PLUS_PLUS_TOK 266
#define MINUS_MINUS_TOK 267
#define MINUS_EQUAL_TOK 268
#define STAR_EQUAL_TOK 269
#define SLASH_EQUAL_TOK 270
#define MOD_EQUAL_TOK 271
#define EQUAL_EQUAL_TOK 272
#define RIGHT_SHIFT_TOK 273
#define GREATER_EQUAL_TOK 274
#define LEFT_SHIFT_TOK 275
#define LESS_EQUAL_TOK 276
#define NOT_EQUAL_TOK 277
#define AND_AND_TOK 278
#define OR_OR_TOK 279
#define XOR_EQUAL_TOK 280

/*....................
.......................*/
/* Identifier, constants..*/
#define INTCONST 350
#define HEADER 351
int nextIdTok = 352; // will be the idtok for next variables
/*....................
.......................*/

// yyin is the file pointer which will be used for input from the file (argv[1])
FILE *yyin;
// output file
FILE *yyout;

// Variable yytext is a pointer to the matched string (NULL-terminated)
char *yytext;
const int YYTEXT_MAX_SIZE = 100;

// length of matched string
int yyleng;

// line no.
int yylineNo;

int stateNo = 0;

// TODO: found out what yylval means
// yylval -> value associated with token

// wrapup, return 1 if done, 0 if not done
int yywrap(void)
{
    fclose(yyin);
    free(yytext);
}

void handle_comment()
{
    stateNo = 0;
    do
        fscanf(yyin, "%c", yytext);
    while (yytext[0] != '\n');
}

int other()
{
    printf("goback");
    fseek(yyin, -1, SEEK_CUR);
    int prevState = stateNo;
    stateNo = 0;

    if (prevState == 1)
        return PLUS_TOK;
    if (prevState == 4)
        return MINUS_TOK;
    if (prevState == 7)
        return STAR_TOK;
    if (prevState == 9)
        return DIVIDE_TOK;
    if (prevState == 12)
        return MOD_TOK;
    if (prevState == 14)
        return EQUAL_TOK;
    if (prevState == 16)
        return GT_TOK;
    if (prevState == 19)
        return LT_TOK;
    if (prevState == 22)
        return NOT_TOK;
    if (prevState == 24)
        return AND_TOK;
    if (prevState == 26)
        return OR_TOK;
    if(prevState == 28)
        return XOR_TOK;

    return -1;
}

int yylex()
{
    fscanf(yyin, "%c", yytext);

    if (yytext[0] == '\n')
        yylineNo++;

    printf("%s\t", yytext);

    if (stateNo == 0) // start
    {
        if (yytext[0] == '+')
            stateNo = 1;
        else if (yytext[0] == '-')
            stateNo = 4;
        else if (yytext[0] == '*')
            stateNo = 7;
        else if (yytext[0] == '/')
            stateNo = 9;
        else if (yytext[0] == '%')
            stateNo = 12;
        else if (yytext[0] == '=')
            stateNo = 14;
        else if (yytext[0] == '>')
            stateNo = 16;
        else if (yytext[0] == '<')
            stateNo = 19;
        else if (yytext[0] == '!')
            stateNo = 22;
        else if (yytext[0] == '&')
            stateNo = 24;
        else if (yytext[0] == '|')
            stateNo = 26;
        else if (yytext[0] == '^')
            stateNo = 28;
        else // TODO: error
            return -1;
    }
    else if (stateNo == 1) // +
    {
        if (yytext[0] == '=') //+=
        {
            stateNo = 0;
            return PLUS_EQUAL_TOK;
        }
        else if (yytext[0] == '+') //++
        {
            stateNo = 0;
            return PLUS_PLUS_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 4) // -
    {
        if (yytext[0] == '-') // --
        {
            stateNo = 0;
            return MINUS_MINUS_TOK;
        }
        else if (yytext[0] == '=') //-=
        {
            stateNo = 0;
            return MINUS_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 7) //*
    {
        if (yytext[0] == '=') //*=
        {
            stateNo = 0;
            return STAR_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 9) // /
    {
        if (yytext[0] == '=') // /=
        {
            stateNo = 0;
            return SLASH_EQUAL_TOK;
        }
        else if (yytext[0] == '/') // //
            handle_comment();
        else
            return other();
    }
    else if (stateNo == 12) // %
    {
        if (yytext[0] == '=') // %=
        {
            stateNo = 0;
            return MOD_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 14) // =
    {
        if (yytext[0] == '=') // ==
        {
            stateNo = 0;
            return EQUAL_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 16) // >
    {
        if (yytext[0] == '>') // >>
        {
            stateNo = 0;
            return RIGHT_SHIFT_TOK;
        }
        else if (yytext[0] == '=') // >=
        {
            stateNo = 0;
            return GREATER_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 19) // <
    {
        if (yytext[0] == '<') // <<
        {
            stateNo = 0;
            return LEFT_SHIFT_TOK;
        }
        else if (yytext[0] == '=') // <=
        {
            stateNo = 0;
            return LESS_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 22) // !
    {
        if (yytext[0] == '=') // !=
        {
            stateNo = 0;
            return NOT_EQUAL_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 24) // &
    {
        if (yytext[0] == '&') // &&
        {
            stateNo = 0;
            return AND_AND_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 26) // |
    {
        if (yytext[0] == '|') // ||
        {
            stateNo = 0;
            return OR_OR_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 28) // ^
    {
        if (yytext[0] == '=') // ^=
        {
            stateNo = 0;
            return XOR_EQUAL_TOK;
        }
        else
            return other();
    }
    else // TODO: error
        stateNo = 0;

    return -1;
}

void main(int argc, char *argv[])
{
    yylineNo = 0;
    int token;
    if (argc != 2)
    {
        printf("Error: add only a filename\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
        perror("fopen() error");

    yytext = (char *)malloc(sizeof(char) * YYTEXT_MAX_SIZE);
    while (!feof(yyin))
    {
        token = yylex();
        printf("%d\n", token);
    }
    yywrap();
}