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
#define IF_TOK 281

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
    printf("goback\n");
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
    if (prevState == 28)
        return XOR_TOK;

    return -1;
}

int yylex()
{
    fscanf(yyin, "%c", yytext);

    if (yytext[0] == '\n')
        yylineNo++;

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
        else if (yytext[0] == 'i')
            stateNo = 30;
        else if (yytext[0] == 'f')
            stateNo = 39;
        else if (yytext[0] == 'c')
            stateNo = 44;
        else if (yytext[0] == 'w')
            stateNo = 50;
        else if (yytext[0] == 'e')
            stateNo = 55;
        else if (yytext[0] == 'l')
            stateNo = 59;
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
    else if (stateNo == 30) // i
    {
        if (yytext[0] == 'n')
            stateNo = 31;
        else if (yytext[0] == 'f')
        {
            stateNo = 0;
            return IF_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 31) // in
    {
        if (yytext[0] == 'c')
            stateNo = 33;
        else if (yytext[0] == 't')
        {
            stateNo = 0;
            return INT_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 33) // inc
    {
        if (yytext[0] == 'l')
            stateNo = 34;
        else
            return other();
    }
    else if (stateNo == 34) // incl
    {
        if (yytext[0] == 'u')
            stateNo = 35;
        else
            return other();
    }
    else if (stateNo == 35) // inclu
    {
        if (yytext[0] == 'd')
            stateNo = 36;
        else
            return other();
    }
    else if (stateNo == 36) // includ
    {
        if (yytext[0] == 'e')
        {
            stateNo = 0;
            return INCLUDE_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 39) // f
    {
        if (yytext[0] == 'l')
            stateNo = 40;
        else if (yytext[0] == 'o')
            stateNo = 48;
        else
            return other();
    }
    else if (stateNo == 40) // fl
    {
        if (yytext[0] == 'o')
            stateNo = 41;
        else
            return other();
    }
    else if (stateNo == 41) // flo
    {
        if (yytext[0] == 'a')
            stateNo = 42;
        else
            return other();
    }
    else if (stateNo == 42) // floa
    {
        if (yytext[0] == 't')
        {
            stateNo = 0;
            return FLOAT_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 48) // fo
    {
        if (yytext[0] == 'r')
        {
            stateNo = 0;
            return FOR_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 44) // c
    {
        if (yytext[0] == 'h')
            stateNo = 45;
        else
            return other();
    }
    else if (stateNo == 45) // ch
    {
        if (yytext[0] == 'a')
            stateNo = 46;
        else
            return other();
    }
    else if (stateNo == 46) // cha
    {
        if (yytext[0] == 'r')
        {
            stateNo = 0;
            return CHAR_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 50) // w
    {
        if (yytext[0] == 'h')
            stateNo = 51;
        else
            return other();
    }
    else if (stateNo == 51) // wh
    {
        if (yytext[0] == 'i')
            stateNo = 52;
        else
            return other();
    }
    else if (stateNo == 52) // whi
    {
        if (yytext[0] == 'l')
            stateNo = 53;
        else
            return other();
    }
    else if (stateNo == 53) // whil
    {
        if (yytext[0] == 'e')
        {
            stateNo = 0;
            return WHILE_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 55) // e
    {
        if (yytext[0] == 'l')
            stateNo = 56;
        else
            return other();
    }
    else if (stateNo == 56) // el
    {
        if (yytext[0] == 's')
            stateNo = 57;
        else
            return other();
    }
    else if (stateNo == 57) // els
    {
        if (yytext[0] == 'e')
        {
            stateNo = 0;
            return ELSE_TOK;
        }
        else
            return other();
    }
    else if (stateNo == 59) // l
    {
        if (yytext[0] == 'o')
            stateNo = 60;
        else
            return other();
    }
    else if (stateNo == 60) // lo
    {
        if (yytext[0] == 'n')
            stateNo = 61;
        else
            return other();
    }
    else if (stateNo == 61) // lon
    {
        if (yytext[0] == 'g')
        {
            stateNo = 0;
            return LONG_TOK;
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
        printf("%s\t%d\n", yytext, token);
    }
    yywrap();
}