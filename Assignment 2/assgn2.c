/*
Compiler Design Assignment 2
Name: Abhiroop Mukherjee
Enrol No.: 510519109
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
#define COMMA_TOK ','
#define DIVIDE_TOK '/'
#define STAR_TOK '*'
#define MOD_TOK '%'
#define NOT_TOK '!'
#define AND_TOK '&'
#define OR_TOK '|'
#define XOR_TOK '^'
#define COMPLEMENT_TOK '~'
#define DEREFERENCE_TOK '.'
#define BACKSLASH_TOK '\\'
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
#define ELSE_TOK 274
#define PLUS_EQUAL_TOK 275
#define PLUS_PLUS_TOK 276
#define MINUS_MINUS_TOK 277
#define MINUS_EQUAL_TOK 278
#define STAR_EQUAL_TOK 279
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
#define RETURN_TOK 282

/*....................
.......................*/
/* Identifier, constants..*/
#define INTCONST 350
#define HEADER 351
#define ID_TOK 352
#define FLOATCONST 351
#define EXPCONST 352
#define STRING_CONST 353
/*....................
.......................*/

// yyin is the file pointer which will be used for input from the file (argv[1])
FILE *yyin;
// output file
FILE *yyout;

// Variable yytext is a pointer to the matched string (NULL-terminated)
char *yytext;
const int YYTEXT_MAX_SIZE = 100;
int yytextIdx;

// length of matched string
int yyleng;

// line no.
int yylineNo;

int stateNo = 0;

// yyval is the value if we returning INTCONST
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
        fscanf(yyin, "%c", &yytext[yytextIdx]);
    while (yytext[yytextIdx] != '\n');
    yylineNo++;

    // clear yytext
    memset(yytext, '\0', YYTEXT_MAX_SIZE); // empty the string
    yytextIdx = -1;                        // to account for ++ at the end of while loop of yylex
}

int other()
{
    // printf("goback\n");
    // we want to go back on place in file so that the
    // FSM can process it from state zero

    // the next character is already in yytext and we also
    // need to get prev char from file

    // so we go back two places
    fseek(yyin, -1, SEEK_CUR);
    // // then read one character again (no we are back one place)
    // fscanf(yyin, "%c", yytext);

    // remove current character from yytext (cause we goin back)
    yytext[yytextIdx] = '\0';
    yytextIdx--;

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
    if (prevState == 32)
        return INT_TOK;
    if (prevState == 38)
        return IF_TOK;
    if (prevState == 43)
        return FLOAT_TOK;
    if (prevState == 49)
        return FOR_TOK;
    if (prevState == 47)
        return CHAR_TOK;
    if (prevState == 54)
        return WHILE_TOK;
    if (prevState == 58)
        return ELSE_TOK;
    if (prevState == 62)
        return LONG_TOK;
    if (prevState == 66)
        return VOID_TOK;
    if (prevState == 72)
        return RETURN_TOK;
    if (prevState >= 30 && prevState <= 73) // characters
        return ID_TOK;
    if (prevState == 74) // integer
        return INTCONST;
    if (prevState == 76) // float
        return FLOATCONST;
    if (prevState == 79) // exponential notation
        return EXPCONST;
    if (prevState == 81) // string const
        return STRING_CONST;

    printf("Error on Line %d\n", yylineNo);
    exit(1);
}

int yylex()
{
    while (1)
    {
        do
        {
            fscanf(yyin, "%c", &yytext[yytextIdx]);

            if (yytext[yytextIdx] == '\n')
                yylineNo++;

        } while (
            yytext[yytextIdx] == '\t' ||
            yytext[yytextIdx] == '\n');

        if(strcmp(yytext, "\0") == 0){
            printf("end\n");
            exit(0);
        }

        if (stateNo == 0) // start
        {
            if (yytext[yytextIdx] == '+')
                stateNo = 1;
            else if (yytext[yytextIdx] == '-')
                stateNo = 4;
            else if (yytext[yytextIdx] == '*')
                stateNo = 7;
            else if (yytext[yytextIdx] == '/')
                stateNo = 9;
            else if (yytext[yytextIdx] == '%')
                stateNo = 12;
            else if (yytext[yytextIdx] == '=')
                stateNo = 14;
            else if (yytext[yytextIdx] == '>')
                stateNo = 16;
            else if (yytext[yytextIdx] == '<')
                stateNo = 19;
            else if (yytext[yytextIdx] == '!')
                stateNo = 22;
            else if (yytext[yytextIdx] == '&')
                stateNo = 24;
            else if (yytext[yytextIdx] == '|')
                stateNo = 26;
            else if (yytext[yytextIdx] == '^')
                stateNo = 28;
            else if (yytext[yytextIdx] == 'i')
                stateNo = 30;
            else if (yytext[yytextIdx] == 'f')
                stateNo = 39;
            else if (yytext[yytextIdx] == 'c')
                stateNo = 44;
            else if (yytext[yytextIdx] == 'w')
                stateNo = 50;
            else if (yytext[yytextIdx] == 'e')
                stateNo = 55;
            else if (yytext[yytextIdx] == 'l')
                stateNo = 59;
            else if (yytext[yytextIdx] == 'v')
                stateNo = 63;
            else if (yytext[yytextIdx] == 'r')
                stateNo = 67;
            else if (isalpha(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else if (isdigit(yytext[yytextIdx]))
                stateNo = 74;
            else if (yytext[yytextIdx] == '#')
                handle_comment(); // preprocessor ignored by yylex
            else if (yytext[yytextIdx] == '"')
                stateNo = 80;
            else if (yytext[yytextIdx] == '{')
                return CURLY_BRACKET_START_TOK;
            else if (yytext[yytextIdx] == '}')
                return CURLY_BRACKET_END_TOK;
            else if (yytext[yytextIdx] == '(')
                return LPAREN_TOK;
            else if (yytext[yytextIdx] == ')')
                return RPAREN_TOK;
            else if (yytext[yytextIdx] == '[')
                return SQUARE_BRACKET_START_TOK;
            else if (yytext[yytextIdx] == ']')
                return SQUARE_BRACKET_END_TOK;
            else if (yytext[yytextIdx] == '.')
                return DEREFERENCE_TOK;
            else if (yytext[yytextIdx] == ';')
                return SEMICOLON_TOK;
            else if (yytext[yytextIdx] == '\\')
                return BACKSLASH_TOK;
            else if (yytext[yytextIdx] == ',')
                return COMMA_TOK;
            else if (yytext[yytextIdx] == '~')
                return COMPLEMENT_TOK;
            else if (yytext[yytextIdx] == ' ')
                ; // ignore
            else
            {
                printf("Error on Line %d\n", yylineNo);
                exit(1);
            }
        }
        else if (stateNo == 1) // +
        {
            if (yytext[yytextIdx] == '=') //+=
            {
                stateNo = 0;
                return PLUS_EQUAL_TOK;
            }
            else if (yytext[yytextIdx] == '+') //++
            {
                stateNo = 0;
                return PLUS_PLUS_TOK;
            }
            else if (isdigit(yytext[yytextIdx]))
                stateNo = 74;
            else
                return other();
        }
        else if (stateNo == 4) // -
        {
            if (yytext[yytextIdx] == '-') // --
            {
                stateNo = 0;
                return MINUS_MINUS_TOK;
            }
            else if (yytext[yytextIdx] == '=') //-=
            {
                stateNo = 0;
                return MINUS_EQUAL_TOK;
            }
            else if (isdigit(yytext[yytextIdx]))
                stateNo = 74;
            else
                return other();
        }
        else if (stateNo == 7) //*
        {
            if (yytext[yytextIdx] == '=') //*=
            {
                stateNo = 0;
                return STAR_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 9) // /
        {
            if (yytext[yytextIdx] == '=') // /=
            {
                stateNo = 0;
                return SLASH_EQUAL_TOK;
            }
            else if (yytext[yytextIdx] == '/') // //
                handle_comment();
            else
                return other();
        }
        else if (stateNo == 12) // %
        {
            if (yytext[yytextIdx] == '=') // %=
            {
                stateNo = 0;
                return MOD_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 14) // =
        {
            if (yytext[yytextIdx] == '=') // ==
            {
                stateNo = 0;
                return EQUAL_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 16) // >
        {
            if (yytext[yytextIdx] == '>') // >>
            {
                stateNo = 0;
                return RIGHT_SHIFT_TOK;
            }
            else if (yytext[yytextIdx] == '=') // >=
            {
                stateNo = 0;
                return GREATER_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 19) // <
        {
            if (yytext[yytextIdx] == '<') // <<
            {
                stateNo = 0;
                return LEFT_SHIFT_TOK;
            }
            else if (yytext[yytextIdx] == '=') // <=
            {
                stateNo = 0;
                return LESS_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 22) // !
        {
            if (yytext[yytextIdx] == '=') // !=
            {
                stateNo = 0;
                return NOT_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 24) // &
        {
            if (yytext[yytextIdx] == '&') // &&
            {
                stateNo = 0;
                return AND_AND_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 26) // |
        {
            if (yytext[yytextIdx] == '|') // ||
            {
                stateNo = 0;
                return OR_OR_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 28) // ^
        {
            if (yytext[yytextIdx] == '=') // ^=
            {
                stateNo = 0;
                return XOR_EQUAL_TOK;
            }
            else
                return other();
        }
        else if (stateNo == 30) // i
        {
            if (yytext[yytextIdx] == 'n')
                stateNo = 31;
            else if (yytext[yytextIdx] == 'f')
                stateNo = 38;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_' || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 38) // if
        {
            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_' || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 31) // in
        {
            if (yytext[yytextIdx] == 't')
                stateNo = 32;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 32) // int
        {
            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 39) // f
        {
            if (yytext[yytextIdx] == 'l')
                stateNo = 40;
            else if (yytext[yytextIdx] == 'o')
                stateNo = 48;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 40) // fl
        {
            if (yytext[yytextIdx] == 'o')
                stateNo = 41;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 41) // flo
        {
            if (yytext[yytextIdx] == 'a')
                stateNo = 42;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 42) // floa
        {
            if (yytext[yytextIdx] == 't')
                stateNo = 43;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 43) // float
        {
            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 48) // fo
        {
            if (yytext[yytextIdx] == 'r')
                stateNo = 49;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 49) // for
        {

            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 44) // c
        {
            if (yytext[yytextIdx] == 'h')
                stateNo = 45;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 45) // ch
        {
            if (yytext[yytextIdx] == 'a')
                stateNo = 46;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 46) // cha
        {
            if (yytext[yytextIdx] == 'r')
                stateNo = 47;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 47) // char
        {

            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 50) // w
        {
            if (yytext[yytextIdx] == 'h')
                stateNo = 51;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 51) // wh
        {
            if (yytext[yytextIdx] == 'i')
                stateNo = 52;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 52) // whi
        {
            if (yytext[yytextIdx] == 'l')
                stateNo = 53;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 53) // whil
        {
            if (yytext[yytextIdx] == 'e')
                stateNo = 54;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 54) // while
        {

            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 55) // e
        {
            if (yytext[yytextIdx] == 'l')
                stateNo = 56;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 56) // el
        {
            if (yytext[yytextIdx] == 's')
                stateNo = 57;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 57) // els
        {
            if (yytext[yytextIdx] == 'e')
                stateNo = 58;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 58) // else
        {
            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 59) // l
        {
            if (yytext[yytextIdx] == 'o')
                stateNo = 60;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 60) // lo
        {
            if (yytext[yytextIdx] == 'n')
                stateNo = 61;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 61) // lon
        {
            if (yytext[yytextIdx] == 'g')
                stateNo = 62;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 62) // long
        {
            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 63) // v
        {
            if (yytext[yytextIdx] == 'o')
                stateNo = 64;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 64) // vo
        {
            if (yytext[yytextIdx] == 'i')
                stateNo = 65;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 65) // voi
        {
            if (yytext[yytextIdx] == 'd')
                stateNo = 66;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 66) // void
        {

            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 67) // r
        {
            if (yytext[yytextIdx] == 'e')
                stateNo = 68;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 68) // re
        {
            if (yytext[yytextIdx] == 't')
                stateNo = 69;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 69) // ret
        {
            if (yytext[yytextIdx] == 'u')
                stateNo = 70;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 70) // retu
        {
            if (yytext[yytextIdx] == 'r')
                stateNo = 71;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 71) // retur
        {
            if (yytext[yytextIdx] == 'n')
                stateNo = 72;
            else if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 72) // return
        {

            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 73) // one or more characters
        {
            if (isalnum(yytext[yytextIdx]) || yytext[yytextIdx] == '_')
                stateNo = 73;
            else
                return other();
        }
        else if (stateNo == 74) // (+ or - or empty)x; where x is a digit
        {
            if (isdigit(yytext[yytextIdx]))
                stateNo = 74;
            else if (yytext[yytextIdx] == '.')
                stateNo = 75;
            else if (yytext[yytextIdx] == 'e')
                stateNo = 77;
            else
                return other();
        }
        else if (stateNo == 75) // (+ or - or empty)(multiple digits).
        {
            if (isdigit(yytext[yytextIdx]))
                stateNo = 76;
            else
                return other();
        }
        else if (stateNo == 76) // (+ or - or empty)(digits).digit
        {
            if (isdigit(yytext[yytextIdx]))
                stateNo = 76;
            else if (yytext[yytextIdx] == 'e')
                stateNo = 77;
            else
                return other();
        }
        else if (stateNo == 77) // (+ or - or empty)(digits).(digits)e OR (+ or - or empty)(digits)e
        {
            if (isdigit(yytext[yytextIdx]))
                stateNo = 79;
            else if (yytext[yytextIdx] == '+' || yytext[yytextIdx] == '-')
                stateNo = 78;
            else
                return other();
        }
        else if (stateNo == 78) // (+ or - or empty)(digits).(digits)e(- or +) OR (+ or - or empty)(digits)e(- or +)
        {
            if (isdigit(yytext[yytextIdx]))
                stateNo = 79;
            else
                return other();
        }
        else if (stateNo == 79) // (+ or - or empty)(digits).(digits)e(- or + or empty) OR (+ or - or empty)(digits)e(- or + or empty)
        {
            if (isdigit(yytext[yytextIdx]))
                stateNo = 79;
            else
                return other();
        }
        else if (stateNo == 80) // "(zero or more characters)
        {
            if (yytext[yytextIdx] == '"')
                stateNo = 81;
            else
                stateNo = 80;
        }
        else if (stateNo == 81) // "(zero or more characters)"
        {
            return other();
        }
        else
        {
            printf("Error on Line %d\n", yylineNo);
            exit(1);
        }

        if (yytext[yytextIdx] != ' ')
            yytextIdx++;
    }
    printf("Error on Line %d\n", yylineNo);
    exit(1);
    return -1;
}

void main(int argc, char *argv[])
{
    yylineNo = 1;
    yytextIdx = 0;
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
        memset(yytext, '\0', YYTEXT_MAX_SIZE); // empty the string
        yytextIdx = 0;
    }
    yywrap();
}